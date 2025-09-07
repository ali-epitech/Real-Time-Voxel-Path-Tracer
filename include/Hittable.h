#ifndef HITTABLE_H
    #define HITTABLE_H

    class Hittable {
        public:
            virtual ~Hittable() = default;
            virtual bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const = 0;
    };

#endif /* HITTABLE_H */