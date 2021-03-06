#ifndef CAMERA_H
#define CAMERA_H

#include "common.h"

class camera {
public:
    camera(
            vec3 position,
            vec3 lookat,
            vec3   vup,
            double vfov, // vertical field-of-view in degrees
            double aspect
    ) {
        auto theta = degrees_to_radians(vfov);
        auto h = tan(theta/2);
        auto viewport_height = 2.0 * h;
        auto viewport_width = aspect * viewport_height;

        auto w = normalize(position- lookat);
        auto u = normalize(cross(vup, w));
        auto v = cross(w, u);

        origin = position;
        horizontal = viewport_width * u;
        vertical = viewport_height * v;
        lower_left_corner = origin - horizontal/2 - vertical/2 - w;
    }

    ray get_ray(double s, double t) const {
        return { origin, lower_left_corner + s*horizontal + t*vertical - origin };
    }

private:
    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
};

#endif //CAMERA_H
