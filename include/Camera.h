#ifndef CAMERA_H
    #define CAMERA_H
    #include "Ray.h"
    #include <glm/glm.hpp>

    class Camera {
        public:
            Camera(const glm::vec3& origin, const glm::vec3& normal, float fov, float t_min, float t_max);
            Ray getRay(float u, float v, int width, int height) const;
            float getTMin() const ;
            float getTMax() const ;
        private:
            glm::vec3 origin;
            glm::vec3 normal;
            float fov; // vertical field of view in degrees
            float t_min; // minimum ray distance
            float t_max; // maximum ray distance
        };

#endif // CAMERA_H
