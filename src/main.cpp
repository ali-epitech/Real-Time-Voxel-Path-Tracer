#include <iostream>
#include "Renderer.h"
#include "Plane.h"
#include "Material.h"

int main()
{
    //Wall description
    auto redMaterial = std::make_shared<Lambertian>(glm::vec3(1.0f, 0.0f, 0.0f));
    glm::vec3 center(0.0f, 1.0f, -5.0f);   // position in world
    glm::vec3 normal(0.0f, 0.0f, 1.0f);    // facing +Z toward the camera
    glm::vec3 uAxis(1.0f, 0.0f, 0.0f);     // horizontal axis along X
    glm::vec3 vAxis(0.0f, 1.0f, 0.0f);     // vertical axis along Y
    float halfWidth = 2.0f;
    float halfHeight = 2.0f;
    auto redWall = std::make_shared<Plane>(center, normal, uAxis, vAxis, halfWidth, halfHeight, redMaterial);

    //camera description
    Camera camera(
        glm::vec3(0.0f, 1.0f, 5.0f),  // origin
        glm::vec3(0.0f, 0.0f, -1.0f), // forward
        45.0f,                        // FOV
        0.001f,                       // t_min
        1000.0f                       // t_max
    );

    //scene init
    Scene scene;
    scene.add(redWall);

    glm::vec3 background_color(1.0f);

    Renderer renderer(800, 600, 100, 5, background_color);
    renderer.render(camera, scene);

    renderer.saveOutput("output.ppm");
    std::cout << "Done! Open output.ppm." << std::endl;

    return 0;
}
