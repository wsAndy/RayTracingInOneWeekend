#pragma once
#include "vec3.h"
#include "ray.h"
#include "color.h"
#include "hittable.h"
#include "interval.h"


/**
判断一个点是否在球上
- 球表面公式：
(x-cx)^2 + (y-cy)^2 + (z-cz)^2 = 0
其中 x,y,z 可以视作球表面在3D空间的点。这个点可以是光线表示，ray = Origin + direction * length;
要求解length，展开后可以得到一元二次方程，length作为未知量。

hit_sphere中的abc就是一元二次方程的参数
 */

template<typename T>
class sphere: public hittable<T>{
    private:
    point3<T> center;
    T radius;
public:
    sphere<T>() {}
    sphere<T>(point3<T> _center, T _radius): center(_center), radius(_radius) {}

    bool hit(const ray<T>& r, interval<T> ray_t, hit_record<T>& rec) const  override {
            
        vec3<T> oc = r.origin() - center;
        auto a = r.direction().length_squared();
        auto half_b = dot(oc, r.direction());
        auto c = oc.length_squared() - radius * radius;

        auto discriminant = half_b * half_b - a*c;
        if( discriminant < 0) return false;

        auto sqrtd = sqrt(discriminant);

        // 在精度范围之内找到最近的解
        auto root = (-half_b - sqrtd)/a;
        if( !ray_t.surrounds(root) ) {
            root = (-half_b + sqrtd)/a;
            if( !ray_t.surrounds(root) ) {
                return false;
            }
        }

        rec.t = root;
        rec.p = r.at(rec.t);

        vec3<T> outward_normal = (rec.p - center) / radius;
        rec.set_face_normal(r, outward_normal);

        return true;
    }
};