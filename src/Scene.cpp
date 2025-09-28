#include "Scene.h"
#include <assimp/Importer.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include <limits>
#include <cstdlib>

// ---------------------------------------------------
// Main Scene hit function
// ---------------------------------------------------
RayInteraction Scene::hit(const Ray& ray, float tMin, float tMax) const
{
    RayInteraction result; // default: no hit
    if (!ai_scene)
        return result;

    float closest = tMax;

    // Iterate over meshes
    for (unsigned int m = 0; m < ai_scene->mNumMeshes; ++m) {
        aiMesh* mesh = ai_scene->mMeshes[m];

        for (unsigned int f = 0; f < mesh->mNumFaces; ++f) {
            const aiFace& face = mesh->mFaces[f];
            glm::vec3 v0(mesh->mVertices[face.mIndices[0]].x,mesh->mVertices[face.mIndices[0]].y,mesh->mVertices[face.mIndices[0]].z);
            glm::vec3 v1(mesh->mVertices[face.mIndices[1]].x,mesh->mVertices[face.mIndices[1]].y,mesh->mVertices[face.mIndices[1]].z);
            glm::vec3 v2(mesh->mVertices[face.mIndices[2]].x,mesh->mVertices[face.mIndices[2]].y,mesh->mVertices[face.mIndices[2]].z);

            float tHit;
            glm::vec3 nHit;
            if (rayTriangleIntersect(ray, v0, v1, v2, tHit, nHit)) {
                if (tHit < closest && tHit > tMin) {
                    closest = tHit;

                    // Directly assign the RayInteraction
                    result.compute(ray,ray.origin + tHit * ray.dir,nHit,ai_scene->mMaterials[mesh->mMaterialIndex], m, f);
                    result.hit = true; // mark hit
                }
            }
        }
    }
    return result;
}

// ---------------------------------------------------
// Ray-triangle intersection (Möller–Trumbore)
// ---------------------------------------------------
bool Scene::rayTriangleIntersect(
    const Ray& ray,
    const glm::vec3& v0,
    const glm::vec3& v1,
    const glm::vec3& v2,
    float& tHit,
    glm::vec3& nHit) const
{
    const float EPSILON = 1e-8f;
    glm::vec3 edge1 = v1 - v0;
    glm::vec3 edge2 = v2 - v0;
    glm::vec3 h = glm::cross(ray.dir, edge2);
    float a = glm::dot(edge1, h);
    if (std::abs(a) < EPSILON)
        return false;

    float f = 1.0f / a;
    glm::vec3 s = ray.origin - v0;
    float u = f * glm::dot(s, h);
    if (u < 0.0f || u > 1.0f) return false;

    glm::vec3 q = glm::cross(s, edge1);
    float v = f * glm::dot(ray.dir, q);
    if (v < 0.0f || u + v > 1.0f) return false;

    tHit = f * glm::dot(edge2, q);
    if (tHit < EPSILON) return false;

    nHit = glm::normalize(glm::cross(edge1, edge2));
    return true;
}
