#include <string>
#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include <chrono>
#include <cmath>
#include "Renderer.h"
#include "Image.h"
#include "Ray.h"
#include <random>
#include "RayInteraction.h"

// ---------------------------------------------------
// Constructor
// ---------------------------------------------------
Renderer::Renderer(int width, int height, int samplesPerPixel, int maxDepth, const glm::vec3& background_color)
:
    width(width),
    height(height),
    image(width, height),
    samplesPerPixel(samplesPerPixel),
    maxDepth(maxDepth),
    background_color(background_color)
{}

// ---------------------------------------------------
// Small number Generator
// ---------------------------------------------------
float randomSmallFloat()
{
    static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
    static std::mt19937 generator(std::random_device{}());
    return distribution(generator);
}

void printProgressBar(int current, int total, int barWidth, std::chrono::steady_clock::time_point startTime)
{
    float progress = float(current) / float(total);
    int pos = int(barWidth * progress);

    // Print bar
    std::cout << "[";
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] ";

    // Percentage
    std::cout << int(progress * 100.0) << "% ";

    // Elapsed time
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();

    // Estimate remaining time
    int eta = 0;
    if (current > 0)
        eta = int(elapsed * (total - current) / current);

    std::cout << "Elapsed: " << elapsed << "s, ETA: " << eta << "s\r";
    std::cout.flush();

    if (current == total) std::cout << std::endl;
}


// ---------------------------------------------------
// Trace a ray recursively
// ---------------------------------------------------
glm::vec3 Renderer::trace(const Ray& ray, int depth, const Camera& camera, const Scene& scene)
{
    if (depth <= 0)
        return glm::vec3(0.0f);

    RayInteraction interaction = scene.hit(ray, camera.getTMin(), camera.getTMax());

    if (!interaction.hit)
        return this->background_color;

    glm::vec3 color = interaction.emitted;

    // Recursively trace all scattered rays
    for (const Ray& next : interaction.nextRays) {
        color += interaction.attenuation * trace(next, depth - 1, camera, scene);
    }

    return color;
}

// ---------------------------------------------------
// Render the full image
// ---------------------------------------------------
void Renderer::render(const Camera& camera, const Scene& scene)
{
    auto startTime = std::chrono::steady_clock::now();

    for (int y = 0; y < this->height; y++) {
        for (int x = 0; x < this->width; x++) {
            glm::vec3 pixelColor(0.0f);

            for (int s = 0; s < this->samplesPerPixel; s++) {
                float u = 2.0f * ((x + randomSmallFloat()) / this->width - 0.5f);
                float v = 2.0f * ((y + randomSmallFloat()) / this->height - 0.5f);
                Ray ray = camera.getRay(u, v, this->width, this->height);
                pixelColor += trace(ray, this->maxDepth, camera, scene);
            }

            pixelColor /= float(this->samplesPerPixel);
            pixelColor = glm::clamp(pixelColor, 0.0f, 1.0f);
            this->image.setPixel(x, y, pixelColor);
        }
        printProgressBar(y + 1, height, 50, startTime);
    }
}

// ---------------------------------------------------
// Save output to file
// ---------------------------------------------------
void Renderer::saveOutput(const std::string& filename)
{
    this->image.savePPM(filename);
}
