
#ifndef CYLINDER_H
#define CYLINDER_H

#include <utility>

#include "common.h"
#include "surface.h"

using std::max;
using std::min;

class cylinder : public surface {
public:
    cylinder(const vec3& cen, const float& he, const float& rad, shared_ptr<material> m) : surface(std::move(m)), center(cen), height(he), radius(rad) {};

    double distance(const vec3& p) const override {
        vec2 xzVec = {p.x()-center.x(), p.z()-center.z()};
        vec2 d = vec2(xzVec.length(), p.y()-center.y()).abs() - vec2(radius, height);
        vec2 newD = {max(d.x(), 0.0), max(d.y(), 0.0)};
        return min(max(d.x(), d.y()), 0.0) + newD.length();
    };

public:
    vec3 center;
    float height;
    float radius;
};



#endif

