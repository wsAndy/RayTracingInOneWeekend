#pragma once

#include "utils.h"

template<typename T>
class interval {
  public:
    T min, max;

    interval() : min(+infinity), max(-infinity) {} // Default interval is empty

    interval(T _min, T _max) : min(_min), max(_max) {}

    bool contains(T x) const {
        return min <= x && x <= max;
    }

    bool surrounds(T x) const {
        return min < x && x < max;
    }

    T clamp(T x) const {
        if(x<min) return min;
        if(x>max) return max;
        return x;
    }

    static const interval<T> empty, universe;
};

const static interval<float> empty   (+infinity, -infinity);
const static interval<float> universe(-infinity, +infinity);

