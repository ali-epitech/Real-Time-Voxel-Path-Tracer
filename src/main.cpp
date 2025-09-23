#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

// Simple container for OpenGL mesh
struct GLMesh {
    GLuint VAO = 0, VBO = 0, EBO = 0;
    size_t indexCount = 0;
    glm::vec3 color;
};

// Process Assimp node recursively
void processNode(const aiNode* node, const aiScene* scene, std::vector<GLMesh>& outMeshes) {
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        const aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        GLMesh glmesh;

        // --- Extract color ---
        aiColor3D color(1.0f, 0.7f, 0.7f);
        if (scene->mMaterials[mesh->mMaterialIndex]->Get(AI_MATKEY_COLOR_DIFFUSE, color) != AI_SUCCESS)
            color = aiColor3D(1.0f, 0.7f, 0.7f);
        glmesh.color = glm::vec3(color.r, color.g, color.b);

        // --- Flatten vertices ---
        std::vector<float> vertices;
        for (unsigned int v = 0; v < mesh->mNumVertices; v++) {
            vertices.push_back(mesh->mVertices[v].x);
            vertices.push_back(mesh->mVertices[v].y);
            vertices.push_back(mesh->mVertices[v].z);
        }

        // --- Flatten indices ---
        std::vector<unsigned int> indices;
        for (unsigned int f = 0; f < mesh->mNumFaces; f++)
            for (unsigned int j = 0; j < mesh->mFaces[f].mNumIndices; j++)
                indices.push_back(mesh->mFaces[f].mIndices[j]);
        glmesh.indexCount = indices.size();

        // --- Setup OpenGL buffers ---
        glGenVertexArrays(1, &glmesh.VAO);
        glGenBuffers(1, &glmesh.VBO);
        glGenBuffers(1, &glmesh.EBO);

        glBindVertexArray(glmesh.VAO);

        glBindBuffer(GL_ARRAY_BUFFER, glmesh.VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glmesh.EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);

        outMeshes.push_back(glmesh);
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++)
        processNode(node->mChildren[i], scene, outMeshes);
}

// Load all GLTF/GLB files in folder
void loadSceneFolder(const std::string& folder, std::vector<GLMesh>& meshes) {
    for (const auto& entry : fs::directory_iterator(folder)) {
        if (entry.is_regular_file()) {
            std::string path = entry.path().string();
            if (path.ends_with(".gltf") || path.ends_with(".glb")) {
                Assimp::Importer importer;
                const aiScene* scene = importer.ReadFile(
                    path,
                    aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_JoinIdenticalVertices
                );
                if (!scene) {
                    std::cerr << "Failed to load: " << path << " Error: " << importer.GetErrorString() << std::endl;
                    continue;
                }
                processNode(scene->mRootNode, scene, meshes);
                std::cout << "Loaded: " << path << std::endl;
            }
        }
    }
}

int main() {
    if (!glfwInit()) { std::cerr << "GLFW init failed\n"; return -1; }

    GLFWwindow* window = glfwCreateWindow(800, 600, "GLTF Folder Viewer", nullptr, nullptr);
    if (!window) { std::cerr << "Failed to create window\n"; glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);

    // <<< Initialize GLAD here >>>
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    // --- Load all meshes from folder ---
    std::vector<GLMesh> meshes;
    loadSceneFolder("../scene", meshes);
    std::cout << "Total meshes loaded: " << meshes.size() << std::endl;

    // --- Simple shader ---
    const char* vertSrc = R"(#version 330 core
    layout(location=0) in vec3 aPos;
    uniform mat4 uModel;
    uniform mat4 uView;
    uniform mat4 uProjection;
    void main(){ gl_Position = uProjection * uView * uModel * vec4(aPos,1.0); })";

    const char* fragSrc = R"(#version 330 core
    out vec4 FragColor;
    uniform vec3 uColor;
    void main(){ FragColor = vec4(uColor,1.0); })";

    auto compileShader = [](GLenum type, const char* src) {
        GLuint s = glCreateShader(type);
        glShaderSource(s, 1, &src, nullptr);
        glCompileShader(s);
        int success; glGetShaderiv(s, GL_COMPILE_STATUS, &success);
        if (!success) { char info[512]; glGetShaderInfoLog(s, 512, nullptr, info); std::cerr << info << std::endl; }
        return s;
    };

    GLuint shader = glCreateProgram();
    GLuint vs = compileShader(GL_VERTEX_SHADER, vertSrc);
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, fragSrc);
    glAttachShader(shader, vs); glAttachShader(shader, fs);
    glLinkProgram(shader);
    glDeleteShader(vs); glDeleteShader(fs);

    // --- Camera ---
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.f/600.f, 0.1f, 100.f);
    glm::mat4 view = glm::lookAt(glm::vec3(0,5,15), glm::vec3(0,2,0), glm::vec3(0,1,0));

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1f,0.1f,0.1f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shader);
        glUniformMatrix4fv(glGetUniformLocation(shader,"uView"),1,GL_FALSE,glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shader,"uProjection"),1,GL_FALSE,glm::value_ptr(projection));

        for (auto& m : meshes) {
            glBindVertexArray(m.VAO);
            glm::mat4 model = glm::mat4(1.0f);
            glUniformMatrix4fv(glGetUniformLocation(shader,"uModel"),1,GL_FALSE,glm::value_ptr(model));
            glUniform3fv(glGetUniformLocation(shader,"uColor"),1,glm::value_ptr(m.color));
            glDrawElements(GL_TRIANGLES, m.indexCount, GL_UNSIGNED_INT, 0);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
