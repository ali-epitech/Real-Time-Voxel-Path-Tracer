#ifndef CAMERA_H
    #define CAMERA_H
    #include "Ray.h"
    #include <glm/glm.hpp>

    class Camera {
        public:
            Camera(const glm::vec3& position, const glm::vec3& look_direction, float fov_deg);

            // Generate a ray through normalized coordinates u,v in [0,1]
            Ray getRay(float u, float v) const;

        private:
            Ray this->ray;   // stores camera position and main direction
            float this->fov; // vertical field of view in degrees
        };

#endif // CAMERA_H
