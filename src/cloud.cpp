#include "cloud.h"

vec3 bg_color(const ray& r) {
    return {0.5, 0.7, 1.0};
//    vec3 unit_direction = r.direction();
//    auto t = 0.5*(unit_direction.y() + 1.0);
//    return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
}

vec3 gardner_cloud::color(const ray& r, vec3 p, vec3 N, std::vector<light> lights) const {
    const int n = 7;

    double X = p.x();
    double Y = p.y();
    double Z = p.z();

    double FX[n];
    double FY[n];
    double C[n];
    double PX[n];
    double PY[n];

    FX[0] = 2*d;
    FY[0] = d/2;
    C[0] = sqrt(d);

//    FX[0] = 3;
//    FY[0] = 3;
//    C[0] = 3;

    double To = rand() / RAND_MAX * 100;

    for (int i = 1; i < n; i++) {
        FX[i] = 2*FX[i-1];
        FY[i] = 2*FX[i-1];
        C[i]  = 0.707*C[i-1];
        PX[i] = pi/2*sin(0.5*FY[i]*Y) + pi*sin(FX[i]*Z/2);
        PY[i] = pi/2*sin(0.5*FX[i]*X) + pi*sin(FX[i]*Z/2);
    }

    double sum1 = 0.0;
    double sum2 = 0.0;

    for (int i = 1; i < n; i++) {
        sum1 += C[i]*sin(FX[i]*X + PX[i] + To);
    }
    for (int i = 0; i < n; i++) {
        sum2 += C[i]*sin(FY[i]*Y + PY[i] + To);
    }

    auto T = (sum1*sum2 + 2) / 5;
    if (T < 0.1) T = 0;
    if (T > 1) T = 1;

    double Ka = 0.2;
    double Kd = 1.0;
    double Ks = 0.4;
    double la = 0.2;
    int spec = 16;

    vec3 E = -r.direction();
    double NE = dot(N, E);

    double color = 0.0;

    for (const light &l : lights) {
        double NL = dot(N, l.L);
        if (NL * NE < 0) {
            continue;
        }
        if (NL < 0 && NE < 0) {
            N = -N;
            NL = dot(N, l.L);
            NE = dot(N, E);
        }
        vec3 R = 2*NL*N - l.L;
        double RE = dot(R, E);
        RE = clamp(RE);

        color += T*(Ks*l.le.x()*pow(RE,spec) + Kd*l.le.x()*NL);
    }

    color += T*Ka*la;

    double step_size = d/100;
    double steps = 0;
    vec3 at = p + r.dir * step_size;
    double de = w->distance_estimator(at);

    while (de < 0) {
        at += r.dir * step_size;
        de = w->distance_estimator(at);
        steps++;
    }

    double dist = steps / (d/step_size);
    if (dist > 1.0) dist = 1.0;

    double fg = dist * color;
//    double fg = color;

    return vec3(fg) + (1 - fg)* bg_color(r);
}

vec3 perlin_cloud::color(const ray& r, vec3 p, vec3 N, std::vector<light> lights) const {
    double step_size = d/100;
    double steps = 0;
    vec3 at = p + r.dir * step_size;
    double de = w->distance_estimator(at);
    double nscale = 5;
    p *= 1.5;
    double noise = pn->noise(p.x()*nscale, p.y()*nscale, p.z());

//    return vec3(noise) + (1-noise)* bg_color(r);

    while (de < 0) {
        at += r.dir * step_size;
        de = w->distance_estimator(at);
        steps++;
    }

    double dist = steps / (d/step_size);
    double fg = dist * dist*dist*dist*dist*noise;

    vec3 Ka(0.2);
    vec3 Kd(1.0);
    vec3 Ks(0.4);
    vec3 la(0.2);
    int spec = 16;

    vec3 E = -r.direction();
    double NE = dot(N, E);

    vec3 color(0.0);

    for (const light &l : lights) {
        double NL = dot(N, l.L);
        if (NL * NE < 0) {
            continue;
        }
        if (NL < 0 && NE < 0) {
            N = -N;
            NL = dot(N, l.L);
            NE = dot(N, E);
        }
        vec3 R = 2*NL*N - l.L;
        double RE = dot(R, E);
        RE = clamp(RE);

        color += 3*fg*(Ks*l.le*pow(RE,spec) + Kd*l.le*NL);
    }

    color += fg*Ka*la;
    vclamp(color);

    return color + (1 - color.x())* bg_color(r);
}
