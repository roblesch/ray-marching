#ifndef SPHERE_H
#define SPHERE_H

#include "common.h"
#include "surface.h"

class sphere : public surface {
public:
    sphere(const vec3& cen, double r, shared_ptr<material> m) :
        surface(std::move(m)), center(cen), radius(r) {};

    double distance(const vec3& p) const override {
        return (p - center).length() - radius;
    };

    vec3 normal(const vec3& p) const override {
        return normalize(p - center);
    };

public:
    vec3 center;
    double radius{};
};

#endif
