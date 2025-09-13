#include <iostream>
#include "Renderer.h"
#include "Triangle.h"
#include "Material.h"
#include "Camera.h"

int main()
{
    Scene scene;

    // ----- Materials -----
    auto red   = std::make_shared<Lambertian>(glm::vec3(0.8f, 0.2f, 0.2f));
    auto green = std::make_shared<Lambertian>(glm::vec3(0.2f, 0.8f, 0.2f));
    auto white = std::make_shared<Lambertian>(glm::vec3(0.8f, 0.8f, 0.8f));
    auto light = std::make_shared<DiffuseLight>(glm::vec3(15.0f, 15.0f, 15.0f));

    // ----- Corners -----
    glm::vec3 floorBL(-5, 0, -10);  // bottom-left floor
    glm::vec3 floorBR( 5, 0, -10);  // bottom-right floor
    glm::vec3 floorFR( 5, 0,  5);   // front-right floor
    glm::vec3 floorFL(-5, 0,  5);   // front-left floor

    glm::vec3 leftBL(-5, 0, -10);   // left wall bottom-left
    glm::vec3 leftTL(-5, 5, -10);   // left wall top-left
    glm::vec3 leftTR(-5, 5,  5);    // left wall top-right
    glm::vec3 leftBR(-5, 0,  5);    // left wall bottom-right

    glm::vec3 rightBL(5, 0, -10);   // right wall bottom-left
    glm::vec3 rightBR(5, 0,  5);    // right wall bottom-right
    glm::vec3 rightTR(5, 5,  5);    // right wall top-right
    glm::vec3 rightTL(5, 5, -10);   // right wall top-left

    glm::vec3 topBL(-5, 5, -10);    // ceiling back-left
    glm::vec3 topBR( 5, 5, -10);    // ceiling back-right
    glm::vec3 topFR( 5, 5,  5);     // ceiling front-right
    glm::vec3 topFL(-5, 5,  5);     // ceiling front-left

    glm::vec3 backBL(-5, 0, -10);   // back wall bottom-left
    glm::vec3 backBR( 5, 0, -10);   // back wall bottom-right
    glm::vec3 backTR( 5, 5, -10);   // back wall top-right
    glm::vec3 backTL(-5, 5, -10);   // back wall top-left

    glm::vec3 lightBL(-1.5f, 4.9f, -4);
    glm::vec3 lightBR( 1.5f, 4.9f, -4);
    glm::vec3 lightTR( 1.5f, 4.9f, -7);
    glm::vec3 lightTL(-1.5f, 4.9f, -7);

    // ----- Geometry -----
    // Floor
    scene.add(std::make_shared<Triangle>(floorBL, floorBR, floorFR, white));
    scene.add(std::make_shared<Triangle>(floorBL, floorFR, floorFL, white));

    // Left wall
    scene.add(std::make_shared<Triangle>(leftBL, leftTL, leftTR, red));
    scene.add(std::make_shared<Triangle>(leftBL, leftTR, leftBR, red));

    // Right wall
    scene.add(std::make_shared<Triangle>(rightBL, rightBR, rightTR, green));
    scene.add(std::make_shared<Triangle>(rightBL, rightTR, rightTL, green));

    // Ceiling / Top wall
    scene.add(std::make_shared<Triangle>(topBL, topBR, topFR, white));
    scene.add(std::make_shared<Triangle>(topBL, topFR, topFL, white));

    // Back wall
    scene.add(std::make_shared<Triangle>(backBL, backBR, backTR, white));
    scene.add(std::make_shared<Triangle>(backBL, backTR, backTL, white));

    // Ceiling light
    scene.add(std::make_shared<Triangle>(lightBL, lightBR, lightTR, light));
    scene.add(std::make_shared<Triangle>(lightBL, lightTR, lightTL, light));

    // ----- Camera -----
    Camera camera(
        glm::vec3(0.0f, 2.5f, 15.0f), // pulled back to see the bigger room
        glm::vec3(0.0f, 0.0f, -1.0f),
        45.0f,
        0.001f,
        1000.0f
    );

    // ----- Renderer -----
    glm::vec3 background_color(0.0f);
    Renderer renderer(800, 600, 1000, 5, background_color);
    renderer.render(camera, scene);
    renderer.saveOutput("output.ppm");

    std::cout << "Done! Open output.ppm." << std::endl;
    return 0;
}
