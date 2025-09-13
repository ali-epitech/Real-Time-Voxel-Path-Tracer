#ifndef PLANE_H
    #define PLANE_H

    #include <glm/glm.hpp>
    #include <memory>
    #include "Ray.h"
    #include "HitRecord.h"
    #include "Hittable.h"

    class Material;

    class Plane : public Hittable{
        public:
            Plane(const glm::vec3& point, const glm::vec3& normal, const glm::vec3& uAxis, const glm::vec3& vAxis, float halfWidth, float halfHeight, const std::shared_ptr<Material>& material);
            bool hit(const Ray& ray, float tMin, float tMax, HitRecord& rec, std::shared_ptr<Material>& material) const override;
            std::shared_ptr<Material> getMaterial() const { return material; }

        private:
            glm::vec3 point;   // a point on the plane (center)
            glm::vec3 normal;  // plane normal (normalized)
            glm::vec3 uAxis;   // local X axis (lies on the plane, normalized)
            glm::vec3 vAxis;   // local Y axis (lies on the plane, normalized)
            float halfWidth;   // half width in u direction
            float halfHeight;  // half height in v direction
            std::shared_ptr<Material> material;
    };

#endif // PLANE_H
