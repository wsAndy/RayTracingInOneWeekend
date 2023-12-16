#pragma once

#include "ray.h"

template <typename T>
class hit_record{
public:
    point3<T> p;
    vec3<T> normal;
    T t;
};

template<typename T>
class hittable{
public:
    virtual ~hittable<T>() = default;
    virtual bool hit(const ray<T>& r, T ray_tmin, T ray_tmax, hit_record<T>& rec) const = 0;
};