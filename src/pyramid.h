
#ifndef PYRAMID_H
#define PYRAMID_H


#include <utility>

#include "common.h"
#include "surface.h"

using std::max;
using std::min;

class pyramid : public surface {
public:
    pyramid(const vec3& cen, const float& he, shared_ptr<material> m) : surface(std::move(m)), center(cen), height(he) {};

    double distance(const vec3& p) const override {
        float m = height * height + 0.25;
        vec2 xzVec = {p.x()-center.x(), p.z()-center.z()};
        xzVec = xzVec.abs();
        if (xzVec.x() < xzVec.y()) {
            double store = xzVec.x();
            xzVec.x(xzVec.y()-0.5);
            xzVec.y( store-0.5);
        }
        else {
            xzVec.x(xzVec.x()-0.5);
            xzVec.y( xzVec.y()-0.5);
        }
        vec3 pVec = {xzVec.x(), p.y()-center.y(), xzVec.y()};

        vec3 q = vec3(pVec.z(), height * pVec.y() - 0.5 * pVec.x(), height*pVec.x() + 0.5 * pVec.y());
        float s = max(-q.x(), 0.0);
        float t = clamp((q.y() - 0.5*p.z())/(m + 0.25), 0.0, 1.0);

        float a = m * (q.x() + s) * (q.x() + s) + q.y() * q.y();
        float b = m * (q.x() + 0.5 * t) * (q.x() + 0.5 * t) + (q.y() - m * t) * (q.y() - m * t);

        float d = 0;
        if (min(q.y(), -q.x() * m - q.y() * 0.5) > 0.0) {
            d = 0.0;
        }
        else {
            d = min(a,b);
        }

        if (max(q.z(), -p.y()) > 0) {
            return sqrt((d + q.z() * q.z())/m);
        }
        else {
            return sqrt((d + q.z() * q.z())/m) * -1;
        }


    };

public:
    vec3 center;
    float height;
};



#endif //RAY_MARCHING_PYRAMID_H
