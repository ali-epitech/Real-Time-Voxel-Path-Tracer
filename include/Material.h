#ifndef MATERIAL_H
    #define MATERIAL_H

    #include <glm/glm.hpp>
    #include "Ray.h"
    #include "HitRecord.h"

    class Material {
        public:
            virtual bool scatter(const Ray& in, const HitRecord& rec, glm::vec3& attenuation, Ray& scattered) const = 0;
            virtual glm::vec3 emitted() const { return glm::vec3(0.0f); }
    };

    class Lambertian : public Material {
        public:
            Lambertian(const glm::vec3& color);
            bool scatter(const Ray& in, const HitRecord& rec, glm::vec3& attenuation, Ray& scattered) const override;
        private:
            glm::vec3 color;
    };

    class DiffuseLight : public Material {
        public:
            DiffuseLight(const glm::vec3& color);
            bool scatter(const Ray& in, const HitRecord& rec, glm::vec3& attenuation, Ray& scattered) const override;
            glm::vec3 emitted() const override;
        private:
            glm::vec3 color;
    };

#endif /* MATERIAL_H */
