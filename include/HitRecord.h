#ifndef HITRECORD_H
#define HITRECORD_H

#include <memory>
#include "Ray.h"
#include "Material.h"
#include <glm/glm.hpp>

class HitRecord {
public:
    HitRecord() = default;
    // getters
    const glm::vec3& getPoint() const { return this->point; }
    const glm::vec3& getNormal() const { return this->normal; }
    float getT() const { return this->t; }
    bool isFrontFace() const { return this->front_face; }
    std::shared_ptr<Material> getMaterial() const { return this->material; }

private:
    glm::vec3 point;       // intersection point
    glm::vec3 normal;      // surface normal at hit
    float t;               // distance along the ray
    bool front_face;       // whether ray hit the front side
    std::shared_ptr<Material> material; // pointer to hit object material
};

#endif // HITRECORD_H
