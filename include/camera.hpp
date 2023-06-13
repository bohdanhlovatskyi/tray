#ifndef CAMERA_
#define CAMERA_

class camera {
    public:
        camera() {
            auto aspect_ratio = 16.0 / 9.0;
            auto viewport_height = 2.0;
            auto viewport_width = aspect_ratio * viewport_height;
            auto focal_length = 1.0;

            origin = vec3::point(0, 0, 0);
            horizontal = vec3::vec(viewport_width, 0.0, 0.0);
            vertical = vec3::vec(0.0, viewport_height, 0.0);
            lower_left_corner = origin - horizontal/2 - vertical/2 - vec3::vec(0, 0, focal_length);
        }

        auto get_ray(double u, double v) const {
            return ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
        }

    private:
        vec3::point origin;
        vec3::point lower_left_corner;
        vec3::vec horizontal;
        vec3::vec vertical;
};

#endif // CAMERA_