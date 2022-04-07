#ifndef DIFFUSE_H
#define DIFFUSE_H

#include <vector>

#include "common.h"
#include "material.h"

// Flat shading
class flat : public material {
public:
    flat(): albedo(vec3::random()) {};
    explicit flat(const vec3& alb): albedo(alb) {};
    vec3 color(const ray& r, double t, vec3 N, std::vector<light> lights) const override;

public:
    vec3 albedo;
};

// Normals visualization
class normals : public material {
public:
    normals() = default;
    vec3 color(const ray& r, double t, vec3 N, std::vector<light> lights) const override;
};

// Diffuse approximation
class diffuse : public material{
public:
    diffuse() : Ka(vec3::random()), Kd(vec3::random()),
        la({0.2, 0.2, 0.2}) {};
    diffuse(vec3 mat_ka, vec3 mat_kd, vec3 l_amb) :
        Ka(mat_ka), Kd(mat_kd), la(l_amb) {};
    vec3 color(const ray& r, double t, vec3 N, std::vector<light> lights) const override;

public:
    vec3 Ka;
    vec3 Kd;
    vec3 la;
};

#endif //DIFFUSE_H
