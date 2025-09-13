#ifndef TRIANGLE_H
    #define TRIANGLE_H

    #include <glm/glm.hpp>
    #include <memory>
    #include "Ray.h"
    #include "HitRecord.h"
    #include "Hittable.h"

    class Triangle : public Hittable {
        public:
            Triangle(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, const std::shared_ptr<Material>& material);
            bool hit(const Ray& ray, float tMin, float tMax, HitRecord& rec, std::shared_ptr<Material>& mat) const override;
            std::shared_ptr<Material> getMaterial() const { return material; }
        private:
            glm::vec3 v0, v1, v2;
            std::shared_ptr<Material> material;
    };

#endif /* TRIANGLE_H */