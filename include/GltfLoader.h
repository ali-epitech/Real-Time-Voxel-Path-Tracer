#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>

class GltfLoader {
public:
    bool load(const std::string& path) {
        scene = importer.ReadFile(path,
            aiProcess_Triangulate |
            aiProcess_GenSmoothNormals |
            aiProcess_JoinIdenticalVertices);
        return scene != nullptr;
    }

    const aiScene* getScene() const { return scene; }

private:
    Assimp::Importer importer;  // must outlive aiScene
    const aiScene* scene = nullptr;
};
