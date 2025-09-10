#ifndef HITRECORD_H
    #define HITRECORD_H

    #include <memory>
    #include <glm/glm.hpp>
    #include "Ray.h"

    class HitRecord {
        public:
            HitRecord() = default;
            void setHit(const glm::vec3& p, const glm::vec3& n, float t_val, const Ray& r);
            const glm::vec3& getPoint() const ;
            const glm::vec3& getNormal() const ;
            float getT() const ;
            bool isFrontFace() const ;

        private:
            glm::vec3 point;       // intersection point
            glm::vec3 normal;      // surface normal at hit
            float t;               // distance along the ray
            bool front_face;       // whether ray hit the front side
    };

#endif // HITRECORD_H
