
#include "material.hpp"
#include "vec.h"
#include "utils.h"
#include "ray.h"

bool lambertian::scatter(
    const ray& r_in, const hit_record& rec, vec3::color& attenuation, ray& scattered
) const {
    (void) r_in;
    vec3::vec scatter_direction = rec.normal + vec3::random_unit_vector();
    // Catch degenerate scatter direction
    if (vec3::vec_near_zero(scatter_direction))
        scatter_direction = rec.normal;
    scattered = ray(rec.p, scatter_direction);
    attenuation = albedo;
    return true;
}

bool metal::scatter(
     const ray& r_in, const hit_record& rec, vec3::color& attenuation, ray& scattered
) const {
    vec3::vec reflected = vec3::reflect(vec3::unit_vector(r_in.direction()), rec.normal);
    scattered = ray(rec.p, reflected);
    attenuation = albedo;
    return scattered.direction().dot(rec.normal) > 0;
}