#ifndef RAY_
#define RAY_

#include <random>

#include "vec.h"

class ray {
public:
    ray(): orig{}, dir{} {}
    ray(const vec3::point& origin, const vec3::vec& direction)
        : orig(origin), dir(direction)
    {}

    inline  vec3::point origin() const  { return orig; }
    inline vec3::vec direction() const { return dir; }
    inline auto at(double t) const { return orig + t*dir; }

public:
    vec3::point orig;
    vec3::vec dir;
};

#endif // RAY_ 