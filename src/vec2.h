#ifndef VEC2_H
#define VEC2_H

#include <algorithm>
#include <cmath>
#include <iostream>
#include <math.h>
using std::sqrt;

class vec2 {
public:
    vec2() : e{0,0} {};

    vec2(double e0) {
        e[0] = e0;
        e[1] = e0;
    }

    vec2(double e0, double e1) {
        e[0] = e0;
        e[1] = e1;
    }

    vec2& operator=(const vec2 &rhs) {
        if (&rhs != this) {
            std::copy_n(rhs.e, 2, e);
        }
        return *this;
    }

    double x() const { return e[0]; }
    double y() const { return e[1]; }

    void x(double d) { e[0] = d; }
    void y(double d) { e[1] = d; }

    double operator[](int i) const { return e[i]; }

    double &operator[](int i) { return e[i]; }

    vec2 operator-() const { return {-e[0], -e[1]}; }

    vec2 &operator+=(const vec2 &v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        return *this;
    }

    vec2 &operator*=(const double t) {
        e[0] *= t;
        e[1] *= t;
        return *this;
    }

    vec2 &operator/=(const double t) {
        return *this *= 1 / t;
    }

    double length() const {
        return sqrt(length_squared());
    }

    double length_squared() const {
        return e[0] * e[0] + e[1] * e[1];
    }

    inline static vec2 random() {
        return { random_double(), random_double() };
    }

    vec2 abs() const{
        return {std::abs(e[0]), std::abs(e[1])};
    }

public:
    double e[2];
};

// vec3 Utility Functions

inline std::ostream &operator<<(std::ostream &out, const vec2 &v) {
    return out << v.e[0] << ' ' << v.e[1];
}

inline vec2 operator+(const vec2 &u, const vec2 &v) {
    return {u.e[0] + v.e[0], u.e[1] + v.e[1]};
}

inline vec2 operator-(const vec2 &u, const vec2 &v) {
    return {u.e[0] - v.e[0], u.e[1] - v.e[1]};
}

inline vec2 operator*(const vec2 &u, const vec2 &v) {
    return {u.e[0] * v.e[0], u.e[1] * v.e[1]};
}

inline vec2 operator*(double t, const vec2 &v) {
    return {t * v.e[0], t * v.e[1]};
}

inline vec2 operator*(const vec2 &v, double t) {
    return t * v;
}

inline vec2 operator/(vec2 v, double t) {
    return (1 / t) * v;
}

inline vec2 operator/(double t, vec2 v) {
    return { t / v.x(), t / v.y()};
}

inline double dot(const vec2 &u, const vec2 &v) {
    return u.e[0] * v.e[0]
           + u.e[1] * v.e[1];
}

inline vec2 cross(const vec2 &u, const vec2 &v) {
    return u.e[0] * v.e[1] - u.e[1] * v.e[0];
}

inline vec2 normalize(vec2 v) {
    return v / v.length();
}

inline void vclamp(vec2 &v) {
    v.x(clamp(v.x()));
    v.y(clamp(v.y()));
}

inline vec2 vmax(vec2 v, double t){
    return { std::max(v.x(),t),
             std::max(v.y(),t)};
}

inline vec2 vmin(vec2 v, double t){
    return { std::min(v.x(),t),
             std::min(v.y(),t)};
}

#endif
