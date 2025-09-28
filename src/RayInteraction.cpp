#include "RayInteraction.h"
#include <glm/gtc/constants.hpp>
#include <glm/gtx/norm.hpp>
#include <cstdlib>
#include <cmath>

// ---------------------------------------------------
// Generate a random unit vector (cosine-weighted diffuse)
// ---------------------------------------------------
glm::vec3 RayInteraction::randomUnitVector() const
{
    float z = static_cast<float>(rand()) / RAND_MAX;
    float phi = 2.0f * glm::pi<float>() * (static_cast<float>(rand()) / RAND_MAX);
    float r = sqrt(1.0f - z * z);
    return glm::vec3(r * cos(phi), r * sin(phi), z);
}

// ---------------------------------------------------
// Compute interaction for a given hit
// ---------------------------------------------------
void RayInteraction::compute(const Ray& incomingRay,const glm::vec3& hitPoint,const glm::vec3& hitNormal,const aiMaterial* material,unsigned int meshIndex,unsigned int faceIndex)
{
    (void) meshIndex;
    (void) faceIndex;

    hit = true;

    // Determine front face
    bool frontFace = glm::dot(incomingRay.dir, hitNormal) < 0;
    glm::vec3 normal = frontFace ? hitNormal : -hitNormal;

    // Default emission
    emitted = glm::vec3(0.0f);
    if (material) {
        aiColor3D emissive(0.f, 0.f, 0.f);
        if (material->Get(AI_MATKEY_COLOR_EMISSIVE, emissive) == AI_SUCCESS)
            emitted = glm::vec3(emissive.r, emissive.g, emissive.b);

        // Diffuse color
        aiColor3D diffuse(1.f, 1.f, 1.f);
        if (material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse) != AI_SUCCESS)
            diffuse = aiColor3D(1.f, 1.f, 1.f);

        attenuation = glm::vec3(diffuse.r, diffuse.g, diffuse.b);

        // Create a scattered ray (Lambertian diffuse)
        Ray scattered(hitPoint, normal + randomUnitVector());
        setSingleRay(scattered);
    } else {
        attenuation = glm::vec3(1.0f);
        nextRays.clear();
    }
}
