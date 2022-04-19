#ifndef CSG_H
#define CSG_H

#include <utility>

#include "common.h"
#include "surface.h"

using std::max;
using std::min;

class csgObject : public surface {
public:
    csgObject(const shared_ptr<surface>& obj1, const shared_ptr<surface>& obj2, int mode,  bool smooth, double smoothLevel, shared_ptr<material> m) : surface(std::move(m)), object1(obj1), object2(obj2), mode(mode), smooth(smooth), smoothLevel(smoothLevel) {};

    double distance(const vec3& p) const override {
        double d1 = object1->distance(p);
        double d2 = object2->distance(p);

        if(!smooth){
            if(mode == UNION){
                return min(d1, d2);
            }
            else if(mode == SUBTRACT){
                return max(-d1, d2);
            }
            else{
                return max(d1, d2);
            }
        }
        else{
            double d = 1e10;
            double dt;
            if(mode == UNION){
                dt = smoothUnion(d1,d2, 0.45);
                return std::min(d, dt);
            }
            else if(mode == SUBTRACT){
                dt = smoothSubtraction(d1,d2, 0.75);
                return std::min(d, dt);
            }
            else{
                dt = smoothIntersection(d1,d2, 0.15);
                return std::min(d, dt);
            }

        }


    };

    double smoothUnion(double d1, double d2, double k) const{
        float h = std::max(k - std::abs(d1 - d2), 0.0);
        return std::min(d1, d2) - h * h * 0.25/k;
    }

    double smoothSubtraction(double d1, double d2, double k) const{
        float h = std::max(k - std::abs(-d1 - d2), 0.0);
        return std::max(-d1, d2) + h * h * 0.25/k;
    }

    double smoothIntersection(double d1, double d2, double k) const{
        float h = std::max(k - std::abs(d1 - d2), 0.0);
        return std::max(d1, d2) + h * h * 0.25/k;
    }

public:
    const shared_ptr<surface> object1;
    const shared_ptr<surface> object2;
    const int mode;
    const bool smooth;
    const double smoothLevel;
};



#endif
