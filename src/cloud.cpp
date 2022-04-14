#include "cloud.h"

double cloud::max_sum = 0.0;
double cloud::min_sum = 0.0;

vec3 bg_color(const ray& r) {
    vec3 unit_direction = r.direction();
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
}

vec3 cloud::color(const ray& r, vec3 p, vec3 N, std::vector<light> lights) const {
    const int n = 4;

    double X = p.x();
    double Y = p.y();
    double Z = p.z();

    double FX[n];
    double FY[n];
    double C[n];
    double PX[n];
    double PY[n];

    FX[0] = 2*pi;
    FY[0] = pi;
    C[0] = 1;
    double To = 1;

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

    auto sum3 = (sum1*sum2);
//    double min = -3;
//    double range = min + 3.56;
//    auto sum4 = (sum3 + min) / range;
//
    cloud::max_sum = sum3 > cloud::max_sum ? sum3 : cloud::max_sum;
    cloud::min_sum = sum3 < cloud::min_sum ? sum3 : cloud::min_sum;
    auto T = (sum1*sum2 + 2) / 5;
    if (T < 0) T = 0;
    if (T > 1) T = 1;
    return vec3(T + (1 - T)*bg_color(r));
}

//vec3 cloud::color(const ray& r, vec3 p, vec3 N, std::vector<light> lights) const {
//    vec3 baseColor = vec3(1);
//    vec3 acc_rgb = vec3(0.0);
//    double acc_a = 0.0;
//
//    vec3 at = p + r.dir * 0.1;
//    double de = w->distance_estimator(at);
//
//    while (de < 0) {
//        acc_rgb += 0.01 * baseColor;
//        acc_a += 0.01;
//        at += r.dir * 0.01;
//        de = w->distance_estimator(at);
//    }
//
//    return acc_rgb*acc_a + bg_color(r)*(1 - acc_a);
//}
