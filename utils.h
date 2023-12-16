#pragma once

#include <cmath>
#include <limits>
#include <memory>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;


const float infinity = std::numeric_limits<float>::infinity();
const double pi = 3.141592653589793;

inline double DEG_TO_RAD(double deg){
    return deg * pi / 180.0;
}
inline float DEG_TO_RAD(float deg){
    return deg * static_cast<float>(pi) / 180.0;
}

#include "ray.h"
#include "vec3.h"
#include "hittable_list.h"