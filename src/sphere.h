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

public:
    vec3 center;
    double radius{};
};

class perturbed_sphere : public sphere {
public:
    perturbed_sphere(const vec3& cen, double r, shared_ptr<material> m) : sphere(cen, r, m) {};

    double distance(const vec3& p) const override {
        double displacement = sin(7.0 * p.x())
                              * sin(7.0 * p.y())
                              * sin(7.0 * p.z()) * 0.1;
        return (p - center).length() - radius + displacement;
    };
};

#endif
