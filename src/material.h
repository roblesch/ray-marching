#ifndef MATERIAL_H
#define MATERIAL_H

#include "common.h"

class material {
public:
    virtual vec3 color(const ray &r, double t) const = 0;
};

class flat : public material {
public:
    flat(): albedo(vec3::random()) {};
    explicit flat(vec3 alb): albedo(alb) {};

    vec3 color(const ray &r, double t) const override {
        return albedo;
    }

public:
    vec3 albedo;
};


#endif //MATERIAL_H
