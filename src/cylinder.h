//
// Created by mathp on 4/17/2022.
//
#ifndef CYLINDER_H
#define CYLINDER_H

#include <utility>

#include "common.h"
#include "surface.h"

using std::max;
using std::min;

class cylinder : public surface {
public:
    cylinder(const vec3& cen, const vec3& dim, shared_ptr<material> m) : surface(std::move(m)), center(cen), dimensions(dim) {};

    double distance(const vec3& p, const float& h, const float& r) const override {
        vec3 q = (p - center).abs() - dimensions;
        return min(max(q.x(), max(q.y(),q.z())), 0.0) + (vmax(q, 0.0)).length();
    };

public:
    vec3 center;
    vec3 dimensions;
    float height;
    float radius;
};



#endif
