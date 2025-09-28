#ifndef RAYINTERACTION_H
    #define RAYINTERACTION_H

    #include <glm/glm.hpp>
    #include <vector>
    #include "Ray.h"
    #include <assimp/material.h>

    class RayInteraction
    {
    public:
        RayInteraction() : hit(false), emitted(0.0f), attenuation(1.0f) {}

        // Was the ray hitting something?
        bool hit;

        // Direct emission from the surface
        glm::vec3 emitted;

        // Fraction of light passed along
        glm::vec3 attenuation;

        // Scattered rays
        std::vector<Ray> nextRays;

        // Convenience for a single scattered ray
        RayInteraction& setSingleRay(const Ray& r)
        {
            nextRays.clear();
            nextRays.push_back(r);
            return *this;
        }

        // Compute the interaction given a hit point, normal, and material
        void compute(const Ray& incomingRay,
                    const glm::vec3& hitPoint,
                    const glm::vec3& hitNormal,
                    const aiMaterial* material,
                    unsigned int meshIndex,
                    unsigned int faceIndex);

    private:
        // Generate random unit vector for diffuse scattering
        glm::vec3 randomUnitVector() const;
    };

#endif // RAYINTERACTION_H
