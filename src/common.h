#ifndef COMMON_H
#define COMMON_H

#include <cmath>
#include <memory>

using std::shared_ptr;

inline double clamp(double d, double max=1.0, double min=0.0) {
    // Clamp a double to a max and min
    return d > max ? max : (d < min ? min : d);
}

inline double drand() {
    // Return a random double (0.0, 1.0)
    return rand() / (RAND_MAX + 1.0);
}

// Common includes
#include "vec3.h"
#include "ray.h"

#endif //COMMON_H
