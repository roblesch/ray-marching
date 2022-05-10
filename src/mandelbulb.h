#ifndef MANDELBULB_H
#define MANDELBULB_H

#include <utility>

#include "common.h"
#include "surface.h"

using std::max;
using std::min;

class mandelbulb : public surface {
public:
    mandelbulb(const vec3& pos, shared_ptr<material> m) : surface(std::move(m)), center(pos) {};
    double distance(const vec3& p) const override {
        vec3 z = p - center;
        double dr =2;
        double r;
        double power = 7; //determines general shape
        for (int i = 0; i < 3; i++) { //determines the fractal iteration complexity
            r = z.length() ;
            if (r > 2) //determines how big the mandelbulb is (fractals are infinite)
                break;
            double theta = acos(z.z() / r) * power;
            double phi = atan2(z.y(), z.x()) * power;
            double zr = pow(r, power);
            dr = pow(r, power - 1) * power * dr + 1;

            z = zr * vec3(sin(theta) * cos(phi) , sin(phi) * sin(theta), cos(theta));
            z += p - center;
        }
        return 0.5 * log (r) * r / dr;
    };

public:
    vec3 center;
};

#endif //MANDELBULB_H
