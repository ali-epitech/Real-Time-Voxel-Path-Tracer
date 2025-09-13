#include "Plane.h"
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

Plane::Plane(const glm::vec3& point, const glm::vec3& normal, const glm::vec3& uAxis, const glm::vec3& vAxis, float halfWidth, float halfHeight, const std::shared_ptr<Material>& material)
:
    point(point),
    normal(glm::normalize(normal)),
    uAxis(glm::normalize(uAxis)),
    vAxis(glm::normalize(vAxis)),
    halfWidth(halfWidth),
    halfHeight(halfHeight),
    material(material)
{}

// Ray-plane intersection (finite plane)
bool Plane::hit(const Ray& ray, float tMin, float tMax, HitRecord& rec, std::shared_ptr<Material>& mat) const
{
    float denom = glm::dot(this->normal, ray.dir);
    if (glm::abs(denom) < 1e-6f) return false; // ray parallel to plane

    //determine at what moment the ray crosed the plane in range
    float t = glm::dot(point - ray.origin, this->normal) / denom;
    if (t < tMin || t > tMax)
        return false;

    //calculating global coordinates
    glm::vec3 hitPoint = ray.at(t);

    // Project hitPoint onto plane's local axes
    //glm::vec3 local = hitPoint - point;
    //float uDist = glm::dot(local, this->uAxis);
    //float vDist = glm::dot(local, this->vAxis);
//
    //// Checking if within bound
    //if (uDist < -(this->halfWidth) || uDist > this->halfWidth) return false;
    //if (vDist < -(this->halfHeight) || vDist > this->halfHeight) return false;

    // Fill HitRecord
    rec.setHit(hitPoint, this->normal, t, ray);
    mat = getMaterial(); // assign material here

    //std::cout << "[PLANE HIT] t=" << t << ", point=" << glm::to_string(rec.point) << ", normal=" << glm::to_string(rec.normal) << "\n";

    return true;
}