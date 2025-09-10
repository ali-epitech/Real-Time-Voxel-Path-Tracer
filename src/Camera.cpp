#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"

Camera::Camera(const glm::vec3& origin, const glm::vec3& normal, float fov, float t_min, float t_max)
:
    origin(origin),
    normal(normal),
    fov(fov),
    t_min(t_min),
    t_max(t_max)
{}

Ray Camera::getRay(float u, float v, int width, int height) const
{
    // Build camera basis
    glm::vec3 w = glm::normalize(-(this->normal));
    glm::vec3 upGuess(0.0f, 1.0f, 0.0f);
    glm::vec3 camRight = glm::normalize(glm::cross(upGuess, w));
    glm::vec3 camUp    = glm::cross(w, camRight);

    // Camera-to-world matrix
    glm::mat4 camToWorld(1.0f);
    camToWorld[0] = glm::vec4(camRight, 0.0f);
    camToWorld[1] = glm::vec4(camUp,    0.0f);
    camToWorld[2] = glm::vec4(-w,       0.0f);
    camToWorld[3] = glm::vec4(origin,   1.0f);

    // Projection matrix
    glm::mat4 proj = glm::perspective(glm::radians(this->fov), float(width)/float(height), this->t_min, this->t_max);

    // actual projection martix
    glm::mat4 invPV = glm::inverse(proj * camToWorld);

    //convert screen pos into 3D pos
    glm::vec4 clip(u, v, -1.0f, 1.0f);
    glm::vec4 worldPos = invPV * clip;
    worldPos /= worldPos.w;

    //defines the actual 3D dir
    glm::vec3 dir = glm::normalize(glm::vec3(worldPos) - origin);
    return Ray(origin, dir);
}


float Camera::getTMin() const
{
    return this->t_min;
}

float Camera::getTMax() const
{
    return this->t_max;
}