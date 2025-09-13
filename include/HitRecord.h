#ifndef HITRECORD_H
    #define HITRECORD_H

    #include <memory>
    #include <glm/glm.hpp>
    #include "Ray.h"

    class HitRecord {
        public:
            HitRecord() = default;
            void setHit(const glm::vec3& p, const glm::vec3& n, float t_val, const Ray& r);
            glm::vec3 point;       // intersection point
            glm::vec3 normal;      // surface normal at hit
            float t;               // distance along the ray
            bool front_face;       // whether ray hit the front side
    };

#endif // HITRECORD_H
