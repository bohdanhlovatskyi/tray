#ifndef VEC_
#define VEC_

#include <cmath>
#include <iostream>
#include <random>

#include <Eigen/Dense>

inline double random_double(double min, double max) {
    static std::uniform_real_distribution<double> distribution(min, max);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double random_double() {
    return random_double(0., 1.);
}

inline auto random_vec() {
    return Eigen::Vector3d{random_double(), random_double(), random_double()};
}

inline auto random_vec(double min, double max) {
    return Eigen::Vector3d{random_double(min, max), random_double(min, max), random_double(min, max)};
}

// TODO: this can be written more efficient 
inline bool vec_near_zero(const Eigen::Vector3d& vec) {
    constexpr auto s = 1e-8;
    return (fabs(vec.x()) < s) && (fabs(vec.y()) < s) && (fabs(vec.z()) < s);
}

// Type aliases for vec3
using vec3 = Eigen::Vector3d;
using point3 = Eigen::Vector3d;   // 3D point
using color = Eigen::Vector3d;    // RGB color

inline std::ostream& operator<<(std::ostream &out, const Eigen::Vector3d &v) {
    return out << v[0] << ' ' << v[1] << ' ' << v[2];
}

inline vec3 unit_vector(const Eigen::Vector3d& v) {
    return v / v.norm();
}

inline vec3 reflect(const Eigen::Vector3d& v, const Eigen::Vector3d& n) {
    return v - 2 * v.dot(n) * n;
}

#endif // VEC_