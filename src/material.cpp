
#include "material.hpp"
#include "vec.h"
#include "ray.h"

bool lambertian::scatter(
    const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
) const {
    (void) r_in;
    vec3 scatter_direction = rec.normal + random_unit_vector();
    // Catch degenerate scatter direction
    if (vec_near_zero(scatter_direction))
        scatter_direction = rec.normal;
    scattered = ray(rec.p, scatter_direction);
    attenuation = albedo;
    return true;
}

bool metal::scatter(
     const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
) const {
    vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
    scattered = ray(rec.p, reflected);
    attenuation = albedo;
    return (scattered.direction().dot(rec.normal) > 0);
}