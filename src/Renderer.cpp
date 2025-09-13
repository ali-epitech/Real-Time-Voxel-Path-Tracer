#include <string>
#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include <chrono>
#include "Renderer.h"
#include "Image.h"
#include "Ray.h"
#include "utils.h"

Renderer::Renderer(int width, int height, int samplesPerPixel, int maxDepth, glm::vec3& background_color)
:
    width(width),
    height(height),
    image(width, height),
    samplesPerPixel(samplesPerPixel),
    maxDepth(maxDepth),
    background_color(background_color)
{}

glm::vec3 Renderer::trace(const Ray& ray, int depth, const Camera& camera, const Scene& scene)
{
    if (depth <= 0) {
        //std::cout << "[TRACE] Reached max recursion depth\n";
        return glm::vec3(0.0f);
    }
    HitRecord rec;
    std::shared_ptr<Material> material;
    if (!scene.hit(ray, camera.getTMin(), camera.getTMax(), rec, material)) {
        //std::cout << "[TRACE] Ray missed: origin=" << glm::to_string(ray.origin) << ", dir=" << glm::to_string(ray.dir) << "\n";
        return this->background_color;
    }
    //std::cout << "[TRACE] Ray hit at t=" << rec.t << ", point=" << glm::to_string(rec.point) << ", normal=" << glm::to_string(rec.normal) << ", depth=" << depth << "\n";
    glm::vec3 emitted = material->emitted();
    Ray scattered;
    glm::vec3 attenuation;
    if (material->scatter(ray, rec, attenuation, scattered)) {
        //std::cout << "[TRACE] Scatter: attenuation=" << glm::to_string(attenuation) << ", scattered dir=" << glm::to_string(scattered.dir) << "\n";
        return emitted + attenuation * trace(scattered, depth - 1, camera, scene);
    } else {
        //std::cout << "[TRACE] Material absorbed the ray\n";
        return emitted;
    }
}

void Renderer::render(const Camera& camera, const Scene& scene)
{
    glm::vec3 pixelColor(0.0f);
    auto startTime = std::chrono::steady_clock::now();
    for (int y = 0; y < this->height; y++) {
        for (int x = 0; x < this->width; x++) {
            for (int s = 0; s < this->samplesPerPixel; s++) {
                float u = 2.0f * ((x + randomFloat()) / this->width - 0.5f); // [-1, 1]
                float v = 2.0f * ((y + randomFloat()) / this->height - 0.5f); // [-1, 1]
                Ray ray = camera.getRay(u, v, this->width, this->height);
                pixelColor += trace(ray, this->maxDepth, camera, scene);
            }
            pixelColor /= float(this->samplesPerPixel);  // average
            pixelColor = glm::clamp(pixelColor, 0.0f, 1.0f);
            this->image.setPixel(x, y, pixelColor);
            //if ((x % 100 == 0) && (y % 100 == 0)) {
            //    std::cout << "[RENDER] Pixel(" << x << "," << y << ") = " << glm::to_string(pixelColor) << "\n";
            //}
        }
        printProgressBar(y + 1, height, 50, startTime);
    }
}

void Renderer::saveOutput(const std::string& filename)
{
    this->image.savePPM(filename);
}