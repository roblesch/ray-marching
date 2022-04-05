#ifndef HIT_RECORD_H
#define HIT_RECORD_H

#include "common.h"
#include "material.h"

struct hit_record {
    vec3 p;
    shared_ptr<material> mat_ptr;
    double t;
};

#endif //HIT_RECORD_H
