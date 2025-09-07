#ifndef MATERIAL_H
    #define MATERIAL_H

    class Material {
        public:
            virtual bool scatter(const Ray& in, const HitRecord& rec, glm::vec3& attenuation, Ray& scattered) const = 0;
            virtual glm::vec3 emitted() const { return glm::vec3(0.0f); }
    };

#endif /* MATERIAL_H */