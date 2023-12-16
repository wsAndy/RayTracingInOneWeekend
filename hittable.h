#pragma once

#include "interval.h"
#include "ray.h"

template <typename T>
class hit_record{
public:
    point3<T> p;
    vec3<T> normal;
    T t;

    bool front_face;

    void set_face_normal(const ray<T>& r, const vec3<T>& outward_normal){
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

template<typename T>
class hittable{
public:
    virtual ~hittable<T>() = default;
    virtual bool hit(const ray<T>& r, interval<T> ray_t, hit_record<T>& rec) const = 0;
};