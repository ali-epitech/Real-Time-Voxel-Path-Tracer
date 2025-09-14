#include <string>
#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include <chrono>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Renderer.h"
#include "Image.h"
#include "Ray.h"
#include "utils.h"

Renderer::Renderer(int width, int height, int samplesPerPixel, int maxDepth, glm::vec3& background_color)
:
    width(width),
    height(height),
    currentSample(0),
    samplesPerPixel(samplesPerPixel),
    maxDepth(maxDepth),
    background_color(background_color)
{
    accumBuffer.resize(width * height, glm::vec3(0.0f));
}

void Renderer::saveOutput(const std::string& filename, std::vector<sf::Uint8> pixels)
{
    std::fstream fd;
    fd.open(filename, std::ios::out);
    if (!fd) {
        std::cout << "Error while creating the file";
    } else {
        std::cout << "File created successfully";
        fd << "P6\n";
        fd << this->width << " " << this->height << "\n";
        fd << "255\n";
        fd.write(reinterpret_cast <char*> (pixels.data()), pixels.size());
        fd.close();
    }
}

glm::vec3 Renderer::trace(const Ray& ray, int depth, const Camera& camera, const Scene& scene)
{
    if (depth <= 0) {
        //std::cout << "[TRACE] Reached max recursion depth\n";
        return glm::vec3(0.0f);
    }
    HitRecord rec;
    std::shared_ptr<Material> material;
    if (!scene.hit(ray, camera.t_min, camera.t_max, rec, material)) {
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

//void Renderer::render(const Camera& camera, const Scene& scene, sf::Texture& texture)
//{
//    glm::vec3 pixelColor(0.0f);
//    auto startTime = std::chrono::steady_clock::now();
//    for (int y = 0; y < this->height; y++) {
//        for (int x = 0; x < this->width; x++) {
//            for (int s = 0; s < this->samplesPerPixel; s++) {
//                float u = 2.0f * ((x + randomFloat()) / this->width - 0.5f); // [-1, 1]
//                float v = 2.0f * ((y + randomFloat()) / this->height - 0.5f); // [-1, 1]
//                Ray ray = camera.getRay(u, v, this->width, this->height);
//                pixelColor += trace(ray, this->maxDepth, camera, scene);
//            }
//            pixelColor /= float(this->samplesPerPixel);  // average
//            pixelColor = glm::clamp(pixelColor, 0.0f, 1.0f);
//            this->image.setPixel(x, y, pixelColor);
//        }
//        printProgressBar(y + 1, height, 50, startTime);
//    }
//    texture.update(this->image.getPixels());
//}

void Renderer::renderNextSample(const Camera& camera, const Scene& scene)
{
    for (int y = 0; y < this->height; y++) {
        for (int x = 0; x < this->width; x++) {
            float u = 2.0f * ((x + randomFloat()) / this->width - 0.5f); // [-1, 1]
            float v = 2.0f * ((y + randomFloat()) / this->height - 0.5f); // [-1, 1]
            Ray ray = camera.getRay(u, v, this->width, this->height);
            glm::vec3 color = trace(ray, this->maxDepth, camera, scene);
            accumBuffer[y * width + x] += color;
        }
    }
    currentSample++;
}

void Renderer::updateTexture(sf::Texture& texture)
{
    std::vector<sf::Uint8> pixels(width * height * 4);

    for (int i = 0; i < width * height; i++) {
        glm::vec3 c = accumBuffer[i] / float(currentSample); // average
        c = glm::clamp(c, 0.0f, 1.0f);
        pixels[i * 4 + 0] = static_cast<sf::Uint8>(c.r * 255);
        pixels[i * 4 + 1] = static_cast<sf::Uint8>(c.g * 255);
        pixels[i * 4 + 2] = static_cast<sf::Uint8>(c.b * 255);
        pixels[i * 4 + 3] = 255;
    }

    texture.update(pixels.data());
    //saveOutput("output.ppm", pixels);
    //return(pixels)
}

bool Renderer::isFinished() const {
    return currentSample >= samplesPerPixel;
}

void Renderer::resetAccumulation()
{
    std::fill(accumBuffer.begin(), accumBuffer.end(), glm::vec3(0.0f));
    currentSample = 0;
}

//void Renderer::clearTexture(sf::Texture& texture)
//{
//    std::vector<sf::Uint8> pixels(width * height * 4, 255); // white
//    texture.update(pixels.data());
//}