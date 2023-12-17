#pragma once
#include <memory>
#include <vector>
#include "hittable.h"

template<typename T>
class hittable_list: public hittable<T>{
    public:
    std::vector<std::shared_ptr<hittable<T>>>  objects;

    hittable_list() {}
    hittable_list(std::shared_ptr<hittable<T>> object) {add(object);}


    void clear() { objects.clear(); }
    void add( std::shared_ptr<hittable<T>> object) {
        objects.push_back(object);
    }

    bool hit(const ray<T>& r, interval<T> ray_t, hit_record<T>& rec) const override {
        hit_record<T> tmp_rec;
        bool hit_anything = false;
        auto closest_so_far = ray_t.max;

        for(const auto& object: objects){
            if(object->hit(r, interval<T>(ray_t.min, closest_so_far), tmp_rec)){
                hit_anything = true;
                closest_so_far = tmp_rec.t;
                rec = tmp_rec;
            }
        }

        return hit_anything;
    }
};

