#include "Camera.h"
#include <glm/glm.hpp>

Camera::Camera(const glm::vec3& origin, const glm::vec3& normal, float fov)
{
    this->origin = origin;
    this->normal = normal;
    this->fov = fov
}