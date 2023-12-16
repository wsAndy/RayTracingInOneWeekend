#pragma once
#include "vec3.h"
#include "ray.h"
#include "color.h"


/**
判断一个点是否在球上
- 球表面公式：
(x-cx)^2 + (y-cy)^2 + (z-cz)^2 = 0
其中 x,y,z 可以视作球表面在3D空间的点。这个点可以是光线表示，ray = Origin + direction * length;
要求解length，展开后可以得到一元二次方程，length作为未知量。

hit_sphere中的abc就是一元二次方程的参数
 */

template<typename T>
T hit_sphere( const point3<T>& center, T radius, const ray<T>& r){
    vec3<T> oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = dot(oc, r.direction());
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = b * b - a*c;
    
    if (discriminant < 0) {
        return -1.0;
    } else {
        return (-b - sqrt(discriminant) ) / a;
    }
}
