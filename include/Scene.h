

#ifndef SCENE_H
    #define SCENE_H

    #include <vector>
    #include <memory>
    #include "Hittable.h"
    #include "HitRecord.h"

    class Scene : public Hittable {
        public:
            Scene() = default;
            void add(const std::shared_ptr<Hittable>& obj);
            bool hit(const Ray& r, float tMin, float tMax, HitRecord& rec, std::shared_ptr<Material>& material) const override;

        private:
            std::vector<std::shared_ptr<Hittable>> objects;
    };

#endif /* SCENE_H */