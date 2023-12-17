#pragma once

#include <cmath>
#include <iostream>
#include <ostream>

using std::sqrt;

template<typename  T>
class vec3{
public:
    T e[3];

    vec3(): e{0,0,0} {}
    
    vec3(T e0, T e1, T e2) : e{e0, e1, e2} {}

    T x() const { return e[0]; }
    T y() const { return e[1]; }
    T z() const { return e[2]; }

    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    T operator[](int i) const { return e[i]; }
    T& operator[](int i) { return e[i]; }

    vec3& operator+=(const vec3 &v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    vec3& operator*=(T t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    vec3& operator/=(T t) {
        return *this *= 1/t;
    }

    T length() const {
        return sqrt(length_squared());
    }

    T length_squared() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }

    static vec3<T> random(){
        return vec3<T>( random_double(), random_double(), random_double() );
    }

    static vec3<T> random(double min, double max) {
        return vec3<T>(random_double(min,max), random_double(min,max), random_double(min,max));
    }
};

template <typename T>
using point3 = vec3<T>;

template <typename T>
inline std::ostream& operator<<(std::ostream &out, const vec3<T> &v){
    return out << v.e[0] << " " << v.e[1] << " " << v.e[2];
}

template <typename T>
inline vec3<T> operator+(const vec3<T> &u, const vec3<T> &v){
    return vec3<T>(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

template <typename T>
inline vec3<T> operator-(const vec3<T> &u, const vec3<T> &v) {
    return vec3<T>(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

template <typename T>
inline vec3<T> operator*(const vec3<T> &u, const vec3<T> &v) {
    return vec3<T>(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

template <typename T>
inline vec3<T> operator*(T t, const vec3<T> &v) {
    return vec3<T>(t*v.e[0], t*v.e[1], t*v.e[2]);
}

template <typename T>
inline vec3<T> operator*(const vec3<T> &v, T t) {
    return t * v;
}

template <typename T>
inline vec3<T> operator/(vec3<T> v, T t) {
    return (1/t) * v;
}

template <typename T>
inline T dot(const vec3<T> &u, const vec3<T> &v) {
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
}

template <typename T>
inline vec3<T> cross(const vec3<T> &u, const vec3<T> &v) {
    return vec3<T>(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

template <typename T>
inline vec3<T> unit_vector(vec3<T> v) {
    return v / v.length();
}

template <typename T>
inline vec3<T> random_in_unit_sphere() {
    while(true){
        auto p = vec3<T>::random(-1,1);
        if(p.length_squared() < 1){
            return p;
        }
    }
}

template <typename T>
inline vec3<T> random_unit_vector() {
    return unit_vector<T>(random_in_unit_sphere<T>());
}

template <typename T>
inline vec3<T> random_on_hemisphere(const vec3<T>& normal){
    auto on_unit_sphere = random_unit_vector<T>();
    if(dot(on_unit_sphere, normal ) > 0.0 ){
        return on_unit_sphere;
    }else{
        return -on_unit_sphere;
    }
}