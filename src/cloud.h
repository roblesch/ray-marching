#ifndef RAY_MARCHING_CLOUD_H
#define RAY_MARCHING_CLOUD_H

#include "material.h"
#include "PerlinNoise.h"
#include "scene.h"

class gardner_cloud : public material {
public:
    gardner_cloud(scene* world, double depth) : w(world), d(depth) {};
    vec3 color(const ray& r, vec3 p, vec3 N, std::vector<light> lights) const override;

public:
    scene* w;
    double d;
};

class perlin_cloud : public material {
public:
    perlin_cloud(scene* world, double depth, PerlinNoise* perlin) : w(world), d(depth), pn(perlin) {};
    vec3 color(const ray& r, vec3 p, vec3 N, std::vector<light> lights) const override;

public:
    scene* w;
    double d;
    PerlinNoise* pn;
};

#endif //RAY_MARCHING_CLOUD_H
