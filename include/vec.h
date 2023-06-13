#ifndef VEC_
#define VEC_

#include <cmath>
#include <iostream>
#include "utils.h"

#include <Eigen/Dense>

namespace vec3 {
    using vec = Eigen::Vector3d;
    using point = Eigen::Vector3d; 
    using color = Eigen::Vector3d;

    vec random_vec();
    vec random_vec(double min, double max);
    vec random_unit_vector();
    vec random_in_unit_sphere();

    bool vec_near_zero(const vec& vec);

    std::ostream& operator<<(std::ostream &out, const vec& v);
    vec unit_vector(const vec& v);
    vec reflect(const vec& v, const vec& n);
}

#endif // VEC_