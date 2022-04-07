#ifndef COMMON_H
#define COMMON_H

#include <cmath>
#include <memory>

/* === Render parameters */

// Image
const auto aspect_ratio = 1;
const int image_width = 400;
const int image_height = static_cast<int>(image_width / aspect_ratio);

// Anti aliasing
const int rays_per_pixel = 100;

/* === */

using std::shared_ptr;
using std::make_shared;

inline double clamp(double d, double max=1.0, double min=0.0) {
    // Clamp a double to a max and min
    return d > max ? max : (d < min ? min : d);
}

inline double random_double() {
    // Return a random double (0.0, 1.0)
    return rand() / (RAND_MAX + 1.0);
}

// Common includes
#include "vec3.h"
#include "ray.h"

#endif //COMMON_H
