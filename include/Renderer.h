#ifndef RENDERER_H
    #define RENDERER_H

    #include "Image.h"
    #include "Camera.h"
    #include "Scene.h"
    #include "HitRecord.h"
    #include "Ray.h"

    class Renderer {
        public:
            Renderer(int width, int height, int samplesPerPixel, int maxDepth, glm::vec3& background_color);
            void render(const Camera& camera, const Scene& scene);
            glm::vec3 trace(const Ray& ray, int depth, const Camera& camera, const Scene& scene);
            void saveOutput(const std::string& filename);
        private:
            int width, height;
            Image image; // The canvas we paint on
            int samplesPerPixel;
            int maxDepth;
            glm::vec3 background_color;
        };

#endif /* RENDERER_H */