#ifndef SPHERE_H
#define SPHERE_H

#include <utility>

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
    perturbed_sphere(const vec3& cen, double r, double phase,
                     double intensity, shared_ptr<material> m) :
                     sphere(cen, r, std::move(m)) {
        ph = phase;
        ints = intensity;
    };

    double distance(const vec3& p) const override {
        double displacement = sin(ph * p.x())
                              * sin(ph * p.y())
                              * sin(ph * p.z()) * ints;
        return (p - center).length() - radius + displacement;
    };

public:
    double ph;
    double ints;
};

#endif
