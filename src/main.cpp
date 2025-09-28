#include <iostream>
#include "Renderer.h"
#include "Camera.h"
#include "Scene.h"
#include "GltfLoader.h"

int main()
{
    // ----- Camera -----
    Camera camera(
        glm::vec3(0.0f, 2.5f, 15.0f), // pulled back to see the bigger room
        glm::vec3(0.0f, 0.0f, 1.0f),
        45.0f,
        0.001f,
        1000.0f
    );

    // ----- Load GLTF/GLB Scene -----
    GltfLoader loader;
    if (!loader.load("../scene/scene.gltf")) {
        std::cerr << "Failed to load scene!" << std::endl;
        return -1;
    }

    // ----- Create Scene wrapper with aiScene pointer -----
    Scene scene;
    scene.setScene(loader.getScene());

    // ----- Renderer -----
    glm::vec3 background_color(0.0f);
    Renderer renderer(800, 600, 1000, 5, background_color);

    // ----- Render -----
    renderer.render(camera, scene);
    renderer.saveOutput("output.ppm");

    std::cout << "Done! Open output.ppm." << std::endl;
    return 0;
}
