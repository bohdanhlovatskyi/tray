#ifndef HITTABLE_
#define HITTABLE_

#include <vector>
#include <memory>

#include "ray.h"

class material;

struct hit_record {
    vec3::point p;
    vec3::vec normal;
    double t;
    std::shared_ptr<material> mat_ptr;
    bool front_face;

    inline void set_face_normal(const ray& r, const vec3::vec& outward_normal) {
        front_face = r.direction().dot(outward_normal) < 0;
        normal = front_face ? outward_normal : -1 * outward_normal;
    }
};

class hittable {
public:
    virtual bool hit(
        const ray& r, double t_min, double t_max, hit_record& rec
    ) const = 0;
};

class hittable_list : public hittable {
    public:
        hittable_list() {}
        inline hittable_list(std::shared_ptr<hittable> object) { add(object); }

        inline void clear() { objects.clear(); }
        inline void add(std::shared_ptr<hittable> object) { objects.push_back(object); }

        virtual bool hit(
            const ray& r, double t_min, double t_max, hit_record& rec) const override;

        ~hittable_list() = default;

    public:
        std::vector<std::shared_ptr<hittable>> objects{};
};

#endif // HITTABLE_
