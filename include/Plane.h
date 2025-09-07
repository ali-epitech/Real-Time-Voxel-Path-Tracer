#ifndef PLANE_H
    #define PLANE_H

    class Plane : public Hittable {
        public:
            Plane(const glm::vec3& point, const glm::vec3& normal);
            virtual bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const override;
        private:
            glm::vec3 this->point;
            glm::vec3 this->normal; // normalized
            std::shared_ptr<Material> this->material;
    };

#endif /* PLANE_H */