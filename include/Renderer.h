#ifndef RENDERER_H
    #define RENDERER_H

    #include <glm/glm.hpp>
    #include <string>
    #include "Image.h"
    #include "Camera.h"
    #include "Scene.h"
    #include "Ray.h"
    #include "RayInteraction.h"

    class Renderer {
    public:
        // Constructor
        Renderer(int width, int height, int samplesPerPixel, int maxDepth, const glm::vec3& background_color);

        // Render the scene from the camera
        void render(const Camera& camera, const Scene& scene);

        // Trace a ray recursively and return its color
        glm::vec3 trace(const Ray& ray, int depth, const Camera& camera, const Scene& scene);

        // Save rendered image to file
        void saveOutput(const std::string& filename);

    private:
        int width, height;
        Image image; // Canvas for output
        int samplesPerPixel;
        int maxDepth;
        glm::vec3 background_color;
    };

#endif // RENDERER_H
