
#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "ray.h"
#include "material.hpp"

class sphere : public hittable {
public:
    sphere() {}
    sphere(vec3::point cen, double r) : center(cen), radius(r) {};
    sphere(vec3::point cen, double r, std::shared_ptr<material> m) : center(cen), radius(r), mat_ptr{m} {};

    virtual bool hit(
        const ray& r, double t_min, double t_max, hit_record& rec) const override;
public:
    vec3::point center;
    double radius;
    std::shared_ptr<material> mat_ptr;
};

inline bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    auto oc = r.origin() - center;
    auto a = r.direction().squaredNorm();
    auto half_b = oc.dot(r.direction());
    auto c = oc.squaredNorm() - radius*radius;

    auto discriminant = half_b*half_b - a*c;
    if (discriminant < 0) return false;
    auto sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    vec3::vec outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;


    return true;
}

#endif