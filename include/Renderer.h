#ifndef RENDERER_H
    #define RENDERER_H

    #include <SFML/Graphics.hpp>
    #include "Image.h"
    #include "Camera.h"
    #include "Scene.h"
    #include "HitRecord.h"
    #include "Ray.h"

    class Renderer {
        public:
            Renderer(int width, int height, int samplesPerPixel, int maxDepth, glm::vec3& background_color);
            //void render(const Camera& camera, const Scene& scene, sf::Texture& texture);
            void renderNextSample(const Camera& camera, const Scene& scene); // adds one sample per pixel
            void updateTexture(sf::Texture& texture); // upload current pixels to GPU
            bool isFinished() const;
            glm::vec3 trace(const Ray& ray, int depth, const Camera& camera, const Scene& scene);
            void resetAccumulation();
            void saveOutput(const std::string& filename, std::vector<sf::Uint8> pixels);
        private:
            int width, height;
            int currentSample;
            int samplesPerPixel;
            int maxDepth;
            glm::vec3 background_color;
            std::vector<glm::vec3> accumBuffer;
        };

#endif /* RENDERER_H */