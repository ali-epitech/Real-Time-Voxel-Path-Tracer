#include "Triangle.h"
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

Triangle::Triangle(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, const std::shared_ptr<Material>& material)
:
    v0(v0),
    v1(v1),
    v2(v2),
    material(material)
{}

bool Triangle::hit(const Ray& ray, float tMin, float tMax, HitRecord& rec, std::shared_ptr<Material>& mat) const
{
    const float EPSILON = 1e-8f;

    glm::vec3 edge1 = v1 - v0;
    glm::vec3 edge2 = v2 - v0;

    glm::vec3 h = glm::cross(ray.dir, edge2);
    float a = glm::dot(edge1, h);

    //std::cout << "exit1\n";

    if (fabs(a) < EPSILON)
        return false; // Ray parallel to triangle
    //std::cout << "exit2\n";

    float f = 1.0f / a;
    glm::vec3 s = ray.origin - v0;
    float u = f * glm::dot(s, h);
    if (u < 0.0f || u > 1.0f)
        return false;
    //std::cout << "exit3\n";

    glm::vec3 q = glm::cross(s, edge1);
    float v = f * glm::dot(ray.dir, q);
    if (v < 0.0f || u + v > 1.0f) {
        //std::cout << "[TRIANGLE] Rejecting ray: u=" << u << ", v=" << v << "\n";
        return false;
    }
    //std::cout << "exit4\n";

    float t = f * glm::dot(edge2, q);
    if (t < tMin || t > tMax)
        tMin += tMax;
    //    return false;
    //std::cout << "exit5\n";
    // Hit confirmed → set hit record
    glm::vec3 hitPoint = ray.at(t);
    glm::vec3 normal   = glm::normalize(glm::cross(edge1, edge2));

    rec.setHit(hitPoint, normal, t, ray);
    mat = getMaterial(); // assign triangle’s material

    return true;
}
