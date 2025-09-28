#ifndef SCENE_H
    #define SCENE_H

    #include <glm/glm.hpp>
    #include "Ray.h"
    #include "RayInteraction.h"
    #include <assimp/scene.h>

    class Scene
    {
    public:
        Scene() = default;

        // Assign a loaded GLTF scene
        void setScene(const aiScene* gltfScene) { ai_scene = gltfScene; }

        // Returns the RayInteraction directly
        RayInteraction hit(const Ray& ray, float tMin, float tMax) const;

    private:
        const aiScene* ai_scene = nullptr;

        bool rayTriangleIntersect(const Ray& ray,const glm::vec3& v0,const glm::vec3& v1,const glm::vec3& v2,float& tHit,glm::vec3& nHit) const;
    };

#endif // SCENE_H