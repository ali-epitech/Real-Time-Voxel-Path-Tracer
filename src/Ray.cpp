#include "Ray.h"
#include <glm/glm.hpp>

Ray::Ray(const glm::vec3& origin, const glm::vec3& direction)
:
    origin(origin),
    dir(glm::normalize(direction))
{}

glm::vec3 Ray::at(float t) const
{
    return this->origin + t * this->dir;
}
