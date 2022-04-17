
#ifndef TRIPRISM_H
#define TRIPRISM_H

#include <utility>

#include "common.h"
#include "surface.h"

using std::max;
using std::min;

class triPrism : public surface {
public:
    triPrism(const vec3& cen, const vec2& he, shared_ptr<material> m) : surface(std::move(m)), center(cen), height(he) {};

    double distance(const vec3& p) const override {
        vec3 q = (p - center).abs();
        return max(q.z()-height.y(), max(q.x()*0.866025+p.y()*0.5, -p.y())-height.x()*0.5);
    };

public:
    vec3 center;
    vec2 height;
};



#endif

