#ifndef PLANE_H
    #define PLANE_H

    class Plane : public Hittable {
        public:
            Plane(const glm::vec3& point, const glm::vec3& normal, std::shared_ptr<Material> mat);
            virtual bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const override;
        private:
            glm::vec3 point;
            glm::vec3 normal; // normalized
            std::shared_ptr<Material> material;
    };

#endif /* PLANE_H */