#include "scene.h"

bool near_zero(double d) {
    // Check if a double is close to 0
    return std::abs(d) < std::numeric_limits<double>::epsilon();
}

double scene::distance_estimator(vec3 p) {
    // Approximate distance between point and nearest surface
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
    // March along a ray by the distance to the nearest surface
    double t = 0;
    while(t < 10) {
        double dist = distance_estimator(r.at(t));
        if (near_zero(dist) || dist < 0) {
            rec.t = t;
            rec.N = nearest->normal(r.at(t));
            rec.mat_ptr = nearest->mat_ptr;
            return true;
        }
        dist = dist < 0.001 ? 0.001 : dist;
        t += dist;
    }
    return false;
}

vec3 scene::ray_color(const ray& r) {
    // Return the color of a surface at the ray intersection if it hits,
    // otherwise return the color of the background
    hit_record rec;
    if (march(r, rec))
        return rec.mat_ptr->color(r, rec.t, rec.N, lights);
    vec3 unit_direction = normalize(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
}
