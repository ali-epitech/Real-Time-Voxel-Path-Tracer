#ifndef HITRECORD_H
    #define HITRECORD_H
    #include "Ray.h"
    #include <glm/glm.hpp>

    class HitRecord {
        public:
            void setFaceNormal(const Ray& r, const glm::vec3& outward_normal);//Checks the face status

            Ray hit_ray; // a ray starting at hit point, pointing along normal or scattered direction
            float t; //the distance along the ray
            bool front_face; // whether the ray hit the front or back side
    };

#endif /* HITRECORD_H */