#include "scene.h"

bool near_zero(double d) {
    return std::abs(d) < std::numeric_limits<double>::epsilon();
}

double scene::DE(vec3 p) {
    double mindist = INT_MAX;
    nearest = surface_list.front();
    for (const shared_ptr<surface>& s : surface_list) {
        double d = s->distance(p);
        if (d < mindist) {
            mindist = d;
            nearest = s;
        }
    }
    return mindist;
}

bool scene::march(const ray& r, hit_record& rec) {
    double t = 0;
    while(t < 10) {
        double dist = DE(r.at(t));
        if (near_zero(dist) || dist < 0) {
            rec.t = t;
            rec.p = r.at(t);
            rec.mat_ptr = nearest->mat_ptr;
            return true;
        }
        dist = dist < 0.001 ? 0.001 : dist;
        t += dist;
    }
    return false;
}

vec3 scene::ray_color(const ray& r) {
    hit_record rec;
    if (march(r, rec))
        return rec.mat_ptr->color(r, rec.t);
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y + 1.0);
    return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
}
