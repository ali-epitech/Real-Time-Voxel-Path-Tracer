#include "Scene.h"

bool Scene::hit(const Ray& r, float t_min, float t_max, HitRecord& rec, std::shared_ptr<Material>& material) const
{
    HitRecord tempRec;
    std::shared_ptr<Material> tempMat;
    bool hitAnything = false;
    float closestSoFar = t_max;

    for (const auto& object : objects) {
        if (object->hit(r, t_min, closestSoFar, tempRec, tempMat)) {
            hitAnything = true;
            closestSoFar = tempRec.getT();
            rec = tempRec;
            material = tempMat;
        }
    }

    return hitAnything;
}

