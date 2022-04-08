#ifndef CAMERA_H
#define CAMERA_H

#include "common.h"

class camera {
public:
    explicit camera(double aspect, const vec3& origin={}) : aspect_ratio(aspect) {};
    ray get_ray(double u, double v) const {
        return { origin, lower_left_corner + u*horizontal + v*vertical - origin };
    }

public:
    double aspect_ratio;
    double viewport_height = 2.0;
    double viewport_width = aspect_ratio * viewport_height;
    double focal_length = 1.0;

    vec3 origin;
    vec3 horizontal = vec3(viewport_width, 0, 0);
    vec3 vertical = vec3(0, viewport_height, 0);
    vec3 lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);
};

#endif //CAMERA_H
