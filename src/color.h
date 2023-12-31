#pragma once

#include "interval.h"
#include "vec3.h"
#include <iostream>

template<typename  T>
using color = vec3<T>;


template<typename  T>
inline T linear_to_gamma(T linear_component)
{
    return pow(linear_component, 1/2.2);
}


template<typename  T>
void write_color(std::ostream &out, color<T> pixel_color, int samples_per_pixel){

    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    auto scale = 1.0 / samples_per_pixel;
    r *= scale;
    g *= scale;
    b *= scale;

    r = linear_to_gamma<T>(r);
    g = linear_to_gamma<T>(g);
    b = linear_to_gamma<T>(b);

    static const interval<T> intensity(0.000, 0.999);
    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(255.0 * intensity.clamp(r)) << ' '
        << static_cast<int>(255.0 * intensity.clamp(g)) << ' '
        << static_cast<int>(255.0 * intensity.clamp(b)) << '\n';
}
