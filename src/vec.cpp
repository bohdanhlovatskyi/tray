#include "vec.h"
#include "utils.h"


vec3::vec vec3::random_vec() {
    return vec3::vec{random_double(), random_double(), random_double()};
}

vec3::vec vec3::random_vec(double min, double max) {
    return vec3::vec{random_double(min, max), random_double(min, max), random_double(min, max)};
}

vec3::vec vec3::random_in_unit_sphere() {
    while (true) {
        vec3::vec p = vec3::random_vec(-1., 1.);
        if (p.squaredNorm() >= 1) continue;
        return p;
    }
}

vec3::vec vec3::random_unit_vector() {
    return vec3::unit_vector(vec3::random_in_unit_sphere());
}

bool vec3::vec_near_zero(const vec& vec) {
    constexpr auto s = 1e-8;
    return (fabs(vec.x()) < s) && (fabs(vec.y()) < s) && (fabs(vec.z()) < s);
}

std::ostream& vec3::operator<<(std::ostream &out, const vec3::vec& v) {
    return out << v[0] << ' ' << v[1] << ' ' << v[2];
}

vec3::vec vec3::unit_vector(const vec3::vec& v) {
    return v / v.norm();
}

vec3::vec vec3::reflect(const vec3::vec& v, const vec3::vec& n) {
    return v - 2 * v.dot(n) * n;
}
