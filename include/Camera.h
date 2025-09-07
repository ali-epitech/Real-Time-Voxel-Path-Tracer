#ifndef CAMERA_H
    #define CAMERA_H
    #include "Ray.h"
    #include <glm/glm.hpp>

    class Camera {
        public:
            Camera(const glm::vec3& origin, const glm::vec3& normal, float fov);

        private:
            glm::vec3 origin;
            glm::vec3 normal;
            float fov; // vertical field of view in degrees
        };

#endif // CAMERA_H
