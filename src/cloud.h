#ifndef RAY_MARCHING_CLOUD_H
#define RAY_MARCHING_CLOUD_H

#include "material.h"
#include "scene.h"

class cloud : public material {
public:
    explicit cloud(scene* world) : w(world) {};
    vec3 color(const ray& r, vec3 p, vec3 N, std::vector<light> lights) const override;

public:
    scene* w;
    static double max_sum;
    static double min_sum;
};

#endif //RAY_MARCHING_CLOUD_H
