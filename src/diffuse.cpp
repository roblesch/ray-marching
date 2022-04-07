#include "diffuse.h"

vec3 flat::color(const ray& r, double t, vec3 N, std::vector<light> lights) const {
    // Flat color
    return albedo;
}

vec3 normals::color(const ray& r, double t, vec3 N, std::vector<light> lights) const {
    // Color as a function of surface normal
    return 0.5*vec3(N.x+1, N.y+1, N.z+1);
}

vec3 diffuse::color(const ray& r, double t, vec3 N, std::vector<light> lights) const {
    // Simple diffuse approximation
    vec3 C;
    double NL;

    for (const light &l : lights) {
        NL = dot(N, l.L);
        C += Kd*l.le*NL;
    }

    C += Ka*la;
    vclamp(C);

    return C;
}
