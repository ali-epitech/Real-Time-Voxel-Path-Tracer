#ifndef RAY_H
    #define RAY_H
    #include <glm/glm.hpp>

    class Ray {
        public:
            Ray(const glm::vec3& origin, const glm::vec3& direction);
            glm::vec3 at(float t) const;
            // getters
            const glm::vec3& getOrigin() const { return origin; }
            const glm::vec3& getDirection() const { return dir; }
        private:
            glm::vec3 origin;
            glm::vec3 dir;
    };

#endif // RAY_H
