#ifndef HIT_RECORD_H
#define HIT_RECORD_H

#include "common.h"
#include "material.h"

// Stores intersection information
struct hit_record {
    double t;
    vec3 N;
    shared_ptr<material> mat_ptr;
};

#endif //HIT_RECORD_H
