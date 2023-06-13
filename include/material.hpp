
#ifndef MATERIAL_H
#define MATERIAL_H

#include "ray.h"
#include "vec.h"
#include "hittable.h"

class material {
public:
    virtual bool scatter(
        const ray& r_in, const hit_record& rec, vec3::color& attenuation, ray& scattered
    ) const = 0;
};

class lambertian : public material {
public:
    lambertian(const vec3::color& a) : albedo(a) {}

    virtual bool scatter(
       const ray& r_in, const hit_record& rec, vec3::color& attenuation, ray& scattere
    ) const override;

public:
    vec3::color albedo;
};

class metal : public material {
public:
    metal(const vec3::color& a) : albedo(a) {}

    virtual bool scatter(
        const ray& r_in, const hit_record& rec, vec3::color& attenuation, ray& scattered
    ) const override;
public:
    vec3::color albedo;
};

#endif // MATERIAL_H