#include <string>
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
        return glm::vec3(0.0f);
    }
    HitRecord rec;
    std::shared_ptr<Material> material;
    if (!scene.hit(ray, camera.getTMin(), camera.getTMax(), rec, material)) {
        return background_color;
    }
    glm::vec3 emitted = material->emitted();
    Ray scattered;
    glm::vec3 attenuation;
    if (material->scatter(ray, rec, attenuation, scattered)) {
        return emitted + attenuation * trace(scattered, depth - 1, camera, scene);
    } else {
        return emitted;
    }
}

void Renderer::render(const Camera& camera, const Scene& scene)
{
    glm::vec3 pixelColor(0.0f);
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
        }
    }
}

void Renderer::saveOutput(const std::string& filename)
{
    this->image.savePPM(filename);
}