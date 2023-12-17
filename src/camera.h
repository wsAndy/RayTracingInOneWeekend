#pragma once

#include "utils.h"
#include "hittable.h"
#include "color.h"

#include <iostream>

template<typename  T>
class camera{
    public:

    
    T aspect_ratio = 16.0/9.0;
    int image_width = 400;
    int samples_per_pixel = 100; 



    void render(const hittable<T>& world){

            
        std::cout << "P3\n" << image_width << " " << image_height << std::endl << "255" << std::endl;

        for(int j = 0; j < image_height; ++j){

            std::clog << "\rScanlines remaining: " << (image_height-j) << " " << std::flush;

            for(int i = 0; i < image_width; ++i){
                color<T> pixel_color(0,0,0);
                for(int sample = 0; sample < samples_per_pixel; ++sample){
                    ray<T> r = get_ray(i,j);
                    pixel_color += ray_color(r, world);
                }
                write_color(std::cout, pixel_color, samples_per_pixel);
            }
        }
        std::clog << "\rDone.   \n" ;

    }

    void initialize(){
            
        image_height = static_cast<int>(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;
        camera_center = point3<T>(0,0,0);


        auto focal_length = 1.0;
        auto viewport_height = 2.0;
        auto viewport_width = viewport_height * (static_cast<T>(image_width) / image_height);

        // Calculate the vectors across the horizontal and down the vertical viewport edges.
        auto viewport_u = vec3<T>(viewport_width, 0, 0);
        auto viewport_v = vec3<T>(0, -viewport_height, 0);

        //Calculate the horizontal and vertical delta vectors from pixel to pixel.
        pixel_delta_u = viewport_u / (T)image_width;
        pixel_delta_v = viewport_v / (T)image_height;

        //Calculate the location of the upper left pixel.
        auto viewport_upper_left = camera_center - vec3<T>(0,0,focal_length) - viewport_u/(T)2.0-viewport_v/(T)2.0;
        pixel00_loc = viewport_upper_left + (T)0.5 * (pixel_delta_u + pixel_delta_v);

    }

private:

    int image_height;
    vec3<T> pixel_delta_u;
    vec3<T> pixel_delta_v;
    point3<T> pixel00_loc;
    point3<T> camera_center;

    ray<T> get_ray(int i, int j) const{
        auto pixel_center = pixel00_loc + ((T)i * pixel_delta_u) + ((T)j * pixel_delta_v);
        auto pixel_sample = pixel_center + pixel_sample_square();

        auto ray_direction = pixel_sample - camera_center;
        return ray<T>(camera_center, ray_direction);
    }

    vec3<T> pixel_sample_square() const {
        // Returns a random point in the square surrounding a pixel at the origin.
        T px = -0.5 + random_double();
        T py = -0.5 + random_double();
        return (px * pixel_delta_u) + (py * pixel_delta_v);
    }

    color<T> ray_color(const ray<T>& r, const hittable<T>& world) const {
        hit_record<T> rec;
        if(world.hit(r, interval<T>(0, infinity), rec))
        {
            vec3 direction = random_on_hemisphere(rec.normal);
            return (T)0.5*( ray_color(ray(rec.p, direction), world) ) ;
        }
            
        vec3<T> unit_direction = unit_vector(r.direction());
        // 归一化向量，y轴-1~1, 映射到a的0~1
        auto a = 0.5 * (unit_direction.y() + 1.0);
        // 在白色到(0.5, 0.7, 1.0) 之间线性渐变
        return (T)(1.0-a) * color<T>(1.0, 1.0, 1.0) + (T)a * color<T>(0.5, 0.7, 1.0);
    }

};