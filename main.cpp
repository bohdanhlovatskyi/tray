// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>

#include <folly/futures/Future.h>
#include <folly/executors/CPUThreadPoolExecutor.h>

// #include "options_parser.h"

#include "include/vec.h"
#include "include/ray.h"
#include "include/utils.h"
#include "include/camera.hpp"
#include "include/sphere.h"
#include "include/hittable.h"
#include "include/material.hpp"

vec3::vec random_in_hemisphere(const vec3::vec& normal) {
    vec3::vec in_unit_sphere = vec3::random_in_unit_sphere();
    if (in_unit_sphere.dot(normal) > 0.0) // In the same hemisphere as the normal
        return in_unit_sphere;
    else
        return -1 * in_unit_sphere;
}

vec3::vec ray_color(const ray& r, const hittable_list& world, int depth) {
    hit_record rec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return vec3::color{0,0,0};

    if (world.hit(r, 0.001, std::numeric_limits<double>::max(), rec)) {
        ray scattered;
        vec3::color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation.array() * ray_color(scattered, world, depth-1).array();
        return vec3::color{0,0,0};
    }

    auto unit_direction = vec3::unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*vec3::color{1.0, 1.0, 1.0} + t*vec3::color{0.5, 0.7, 1.0};
}


void write_color(std::ostream &out, vec3::color pixel_color, uint samples_per_pixel) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Divide the color by the number of samples.
    auto scale = 1.0 / samples_per_pixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}

const int samples_per_pixel = 100;
const int max_depth = 50;

folly::SemiFuture<vec3::color> ColorInPixel(
    int i, int j,
    int image_width, int image_height,
    const camera& cam, 
    const hittable_list& scene
) {
    vec3::color pixel_color(0, 0, 0);
    for (int s = 0; s < samples_per_pixel; ++s) {
        auto u = (i + random_double()) / (image_width-1);
        auto v = (j + random_double()) / (image_height-1);
        ray r = cam.get_ray(u, v);
        pixel_color += ray_color(r, scene, max_depth);
    }

    return pixel_color;
}

int main(int argc, char* argv[]) {
    (void) argc; (void) argv;
    
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 200;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    hittable_list scene;
    auto material_ground = std::make_shared<lambertian>(vec3::color(0.5, 0.5, 0.5));
    auto material_center = std::make_shared<lambertian>(vec3::color(1., 0.0, 0.2));
    auto material_left   = std::make_shared<metal>(vec3::color(0.8, 0.8, 0.8));
    auto material_right  = std::make_shared<metal>(vec3::color(0.8, 0.6, 0.2));

    scene.add(std::make_shared<sphere>(vec3::point( 0.0, -100.5, -1.0), 100.0, material_ground));
    scene.add(std::make_shared<sphere>(vec3::point( 0.0,    0.0, -1.0),   0.5, material_center));
    scene.add(std::make_shared<sphere>(vec3::point(-1.0,    0.0, -1.0),   0.5, material_left));
    scene.add(std::make_shared<sphere>(vec3::point( 1.0,    0.0, -1.0),   0.5, material_right));

    // auto scene = random_scene();

    // Camera
    camera cam;

    std::vector<folly::Future<vec3::color>> futures;
    futures.reserve(image_height * image_width);

    folly::CPUThreadPoolExecutor executor{2};

    for (int j = image_height-1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {
            auto future = std::move(
                ColorInPixel(i, j, image_width, image_height, cam, scene)
            ).via(&executor);
            futures.push_back(std::move(future));
        }
    }
    folly::collectAll(futures).wait();

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for (int j = image_height-1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {
            write_color(
                std::cout,
                std::move(futures[(image_height - 1 - j)*image_width + i]).value(),
                samples_per_pixel
            );
        }
    }

    return 0;
}
