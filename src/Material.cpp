#include "Material.h"
#include "HitRecord.h"
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/random.hpp>

// Lambertian constructor
Lambertian::Lambertian(const glm::vec3& color)
:
    color(color)
{}

// Lambertian scatter
bool Lambertian::scatter(const Ray& in, const HitRecord& rec, glm::vec3& attenuation, Ray& scattered) const
{
    (void)in;
    glm::vec3 scatter_direction = rec.normal + glm::sphericalRand(1.0f);
    // Catch degenerate scatter direction
    if (glm::length(scatter_direction) < 1e-8f)
        scatter_direction = rec.normal;
    scattered = Ray(rec.point, scatter_direction);
    attenuation = this->color; // use the stored color
    return true;
}


// DiffuseLight constructor
DiffuseLight::DiffuseLight(const glm::vec3& color):
    color(color)
{}

// DiffuseLight scatter
bool DiffuseLight::scatter(const Ray& in, const HitRecord& rec, glm::vec3& attenuation, Ray& scattered) const
{
    (void)in;
    (void)rec;
    (void)attenuation;
    (void)scattered;
    return false;
}

// DiffuseLight emitted
glm::vec3 DiffuseLight::emitted() const
{
    return this->color;
}
