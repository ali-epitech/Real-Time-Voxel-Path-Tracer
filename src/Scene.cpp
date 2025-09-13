#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include "Scene.h"

bool Scene::hit(const Ray& ray, float t_min, float t_max, HitRecord& rec, std::shared_ptr<Material>& mat) const
{
    bool hitAnything = false;
    float closestSoFar = t_max;

    for (const auto& object : objects) {
        //std::cout << "[SCENE] Testing object...\n";
        if (object->hit(ray, t_min, closestSoFar, rec, mat)) {
            hitAnything = true;
            closestSoFar = rec.t;
            //std::cout << "[SCENE] Hit! t=" << closestSoFar << "\n";
        }
    }

    return hitAnything;
}



void Scene::add(const std::shared_ptr<Hittable>& object)
{
    this->objects.push_back(object);
}
