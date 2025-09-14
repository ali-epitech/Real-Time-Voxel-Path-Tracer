#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
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
    glm::vec3 forward = glm::normalize(-normal);
    glm::vec3 right   = glm::normalize(glm::cross(glm::vec3(0,1,0), forward));
    glm::vec3 up      = glm::cross(forward, right);

    float aspect = float(width)/float(height);
    float fovScale = tan(glm::radians(fov) * 0.5f);

    float px = u * aspect * fovScale;
    float py = v * fovScale;

    glm::vec3 dir = glm::normalize(forward + px * right + py * up);
    return Ray(origin, dir);
}

void Camera::moveForward(float delta)
{
    origin += glm::normalize(-normal) * delta;
    moved = true;
}

void Camera::moveBackward(float delta)
{
    origin -= glm::normalize(-normal) * delta;
    moved = true;
}

void Camera::moveRight(float delta)
{
    glm::vec3 right = glm::normalize(glm::cross(glm::vec3(0,1,0), -normal));
    origin += right * delta;
    moved = true;
}

void Camera::moveLeft(float delta)
{
    glm::vec3 right = glm::normalize(glm::cross(glm::vec3(0,1,0), -normal));
    origin -= right * delta;
    moved = true;
}

void Camera::moveUp(float delta)
{
    origin += glm::vec3(0,1,0) * delta;
    moved = true;
}

void Camera::moveDown(float delta)
{
    origin -= glm::vec3(0,1,0) * delta;
    moved = true;
}
