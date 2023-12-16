#include <iostream>
#include <memory>
#include "utils.h"
#include "color.h"
#include "sphere.h"

#include "camera.h"

using GType=float;

int main(){

    auto camera = std::make_shared<::camera<GType>>();
    camera.get()->initialize();


    // World
    
    hittable_list<GType> world;

    world.add( std::make_shared<::sphere<GType>>(point3<GType>(0, 0, -1), 0.5) );

    world.add( std::make_shared<::sphere<GType>>(point3<GType>(0, -100.5, -1), 100) ); 


    // Camera
    camera->render(world);


    return 0;
}