

#ifndef SCENE_H
    #define SCENE_H
    #include <vector>

    class Scene {
        public:
            void add(std::shared_ptr<Hittable> obj);
            bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const;

        private:
            std::vector<std::shared_ptr<Hittable>> objects;
    };

#endif /* SCENE_H */