#include "cloud.h"

vec3 cloud::color(const ray &r, vec3 p, vec3 N, std::vector<light> lights) const {
    vec3 invRay = 1.0 / p;
    vec3 tbottom = -invRay * vec3(0.5);
    vec3 ttop = invRay * (vec3(1.0) - vec3(0.5));

    vec3 tmin = min(ttop, tbottom);
    vec3 tmax = max(ttop, tbottom);

    double largestMin = std::max(std::max(tmin.x(), tmin.y()), std::max(tmin.x(), tmin.z()));
    double smallestMax = std::min(std::min(tmax.x(), tmax.y()), std::min(tmax.x(), tmax.z()));

    double near = largestMin;
    double far = smallestMax;

    return vec3(0.5) + near * p;
}
