#include <iostream>
#include <memory>
#include "utils.h"
#include "color.h"
#include "sphere.h"

using GType=float;

template<typename T>
color<T> ray_color(const ray<T>& r, const hittable<T>& world){

    hit_record<T> rec;
    if(world.hit(r, interval<T>(0, infinity), rec))
    {
        return (T)0.5*(rec.normal + color<T>(1, 1, 1) ) ;
    }
        
    vec3<T> unit_direction = unit_vector(r.direction());
    // 归一化向量，y轴-1~1, 映射到a的0~1
    auto a = 0.5 * (unit_direction.y() + 1.0);
    // 在白色到(0.5, 0.7, 1.0) 之间线性渐变
    return (T)(1.0-a) * color<T>(1.0, 1.0, 1.0) + (T)a * color<T>(0.5, 0.7, 1.0);
}

int main(){
    // Image 
    auto aspect_ratio = 16.0/9.0;
    int image_width = 400;

    int image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // World

    hittable_list<GType> world;

    world.add( std::make_shared<::sphere<GType>>(point3<GType>(0, 0, -1), 0.5) );

    world.add( std::make_shared<::sphere<GType>>(point3<GType>(0, -100.5, -1), 100) ); 


    // Camera

    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (static_cast<GType>(image_width) / image_height);
    auto camera_center = point3<GType>(0,0,0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewport_u = vec3<GType>(viewport_width, 0, 0);
    auto viewport_v = vec3<GType>(0, -viewport_height, 0);

    //Calculate the horizontal and vertical delta vectors from pixel to pixel.
    auto pixel_delta_u = viewport_u / (GType)image_width;
    auto pixel_delta_v = viewport_v / (GType)image_height;

    //Calculate the location of the upper left pixel.
    auto viewport_upper_left = camera_center - vec3<GType>(0,0,focal_length) - viewport_u/(GType)2.0-viewport_v/(GType)2.0;
    auto pixel00_loc = viewport_upper_left + (GType)0.5 * (pixel_delta_u + pixel_delta_v);


    std::cout << "P3\n" << image_width << " " << image_height << std::endl << "255" << std::endl;

    for(int j = 0; j < image_height; ++j){

        std::clog << "\rScanlines remaining: " << (image_height-j) << " " << std::flush;

        for(int i = 0; i < image_width; ++i){
            
            auto pixel_center = pixel00_loc + ((GType)i * pixel_delta_u) + ((GType)j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            ray<GType> r(camera_center, ray_direction);
            color<GType> pixel_color = ray_color(r, world);

            write_color(std::cout, pixel_color);
        }
    }
    std::clog << "\rDone.   \n" ;
    return 0;
}