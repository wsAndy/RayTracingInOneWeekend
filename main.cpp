#include <iostream>
#include "vec3.h"
#include "color.h"

using GType=float;

int main(){
    // Image 
    int image_width = 512;
    int image_height = 512;

    std::cout << "P3\n" << image_width << " " << image_width << std::endl << "255" << std::endl;

    for(int j = 0; j < image_height; ++j){

        std::clog << "\rScanlines remaining: " << (image_height-j) << " " << std::flush;

        for(int i = 0; i < image_width; ++i){
            auto pixel_color = color<GType>( GType(i)/(image_width-1), GType(j)/(image_height-1), 0 );
            write_color(std::cout, pixel_color);
        }
    }
    std::clog << "\rDone.   \n" ;
    return 0;
}