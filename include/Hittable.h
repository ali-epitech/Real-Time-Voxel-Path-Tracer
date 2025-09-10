#ifndef HITTABLE_H
    #define HITTABLE_H
    #include <glm/glm.hpp>
    #include "HitRecord.h"
    #include "Material.h"

    class Hittable {
        public:
            virtual ~Hittable() = default;
            virtual bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec, std::shared_ptr<Material>& material) const = 0;
            virtual std::shared_ptr<Material> getMaterial() const ;
    };

#endif /* HITTABLE_H */