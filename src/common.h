#ifndef COMMON_H
#define COMMON_H

#include <cmath>
#include <memory>

using std::shared_ptr;
using std::make_shared;

const double pi = 3.1415926535897932385;
const int UNION = 0;
const int SUBTRACT = 1;
const int INTERSECT = 2;

inline double clamp(double d, double max=1.0, double min=0.0) {
    // Clamp a double to a max and min
    return d > max ? max : (d < min ? min : d);
}

inline double random_double() {
    // Return a random double (0.0, 1.0)
    return rand() / (RAND_MAX + 1.0);
}

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

// Common includes
#include "vec3.h"
#include "ray.h"

/* === Render parameters */

// Camera
const double fov = 90;
const double aspect_ratio = 1;
const vec3 camera_origin(0, 0, 0);
const vec3 camera_lookat(0, 0, -1);
const vec3 camera_up(0, 1, 0);

// Image
const int image_width = 400;
const int image_height = static_cast<int>(image_width / aspect_ratio);

// Anti aliasing
const int rays_per_pixel = 10;

// Parallelization
const bool RENDER_PARALLEL = false;

/* === */

#endif //COMMON_H
