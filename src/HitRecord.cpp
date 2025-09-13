#include <glm/glm.hpp>
#include "HitRecord.h"

void HitRecord::setHit(const glm::vec3& p, const glm::vec3& n, float t_val, const Ray& r)
{
    this->point = p;
    this->front_face = glm::dot(r.dir, n) < 0;
    this->normal = this->front_face ? n : -n;
    this->t = t_val;
}