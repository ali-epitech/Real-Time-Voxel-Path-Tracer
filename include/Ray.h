#ifndef RAY_H
    #define RAY_H
    #include <glm/glm.hpp>

    class Ray {
        public:
            Ray() = default;
            Ray(const glm::vec3& origin, const glm::vec3& direction);
            glm::vec3 at(float t) const;
            glm::vec3 origin;
            glm::vec3 dir;
            // getters
            const glm::vec3& getDirection() const { return dir; }
        private:
    };

#endif // RAY_H
