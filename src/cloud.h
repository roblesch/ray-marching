#ifndef RAY_MARCHING_CLOUD_H
#define RAY_MARCHING_CLOUD_H

#include "material.h"

class cloud : public material {
public:
    cloud() = default;
    vec3 color(const ray& r, vec3 p, vec3 N, std::vector<light> lights) const override;
};

#endif //RAY_MARCHING_CLOUD_H
