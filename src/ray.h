#ifndef RAY_
#define RAY_

#include <random>

#include "vec.h"

class ray {
public:
    ray(): orig{}, dir{} {}
    ray(const point3& origin, const vec3& direction)
        : orig(origin), dir(direction)
    {}

    point3 origin() const  { return orig; }
    vec3 direction() const { return dir; }
    inline auto at(double t) const {
        return orig + t*dir;
    }

public:
    point3 orig;
    vec3 dir;
};


inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

inline auto random_in_unit_sphere() {
    while (true) {
        auto p = random_vec(-1., 1.);
        if (p.squaredNorm() >= 1) continue;
        return p;
    }
}

inline auto random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}

#endif // RAY_ 