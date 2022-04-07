#ifndef MATERIAL_H
#define MATERIAL_H

#include <vector>

#include "common.h"
#include "light.h"
#include "surface.h"

class material {
public:
    virtual vec3 color(const ray &r, double t, vec3 N, std::vector<light> lights) const = 0;
};

#endif //MATERIAL_H
