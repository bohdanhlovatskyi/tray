
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

#endif