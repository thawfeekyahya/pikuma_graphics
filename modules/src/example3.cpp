#include <iostream>
#include "example3.h"
#include "util.h"


using namespace std;
using namespace pikuma::utility;

Example3::Example3() {
}

void Example3::initialize() {
   std::cout<<"Example3 - Plot 9x9x9 Cubes and rotate along x y and z"<<std::endl;
   populate_dot_array_cube();
}

void Example3::populate_dot_array_cube() {

    int point_count = 0;
    
    for (float x=-1; x <= 1; x+= 0.25) {
        for (float y=-1; y <=1; y+=0.25) {
            for (float z=-1; z<=1; z+=0.25) {
                Vector3d new_point(x,y,z);
                cube_points[point_count++] = new_point;
            }
        }
    }
}

void Example3::update() {
   

    //Rotation
    cube_rotation.set_y(cube_rotation.get_y() + 0.01);
    cube_rotation.set_x(cube_rotation.get_x() + 0.01);
    cube_rotation.set_z(cube_rotation.get_z() + 0.01);

    for (int i=0; i< N_POINTS; i++) {
        Vector3d point = cube_points[i];

        
        Vector3d transformed_point = point.rotate_x(cube_rotation.get_x());
        transformed_point = transformed_point.rotate_y(cube_rotation.get_y());
        transformed_point = transformed_point.rotate_z(cube_rotation.get_z());
        //

        //Push camera after rotation
        transformed_point.set_z(transformed_point.get_z() - camera_pos.get_z());

        //Push camera with orignal points (before tranformation) 
        //point.set_z(point.get_z() - camera_pos.get_z());
        //Vector2d projected_point = project(point);

        Vector2d projected_point = project(transformed_point);
        projected_points[i] = projected_point;
    }
}

void Example3::render() {
    setup_render();    


    for (int i =0; i< N_POINTS; i++) {
        Vector2d projected_point = projected_points[i];
        draw_rectangle(
          projected_point.get_x() + (screen_width * 0.5), 
          projected_point.get_y()+ (screen_height * 0.5),
          4,4,
          0xFFFFFF00
        );

    }

    clear_render();
}

void Example3::process_input() {
   std::cout<<"process_input Example 3"<<std::endl;
}


Vector2d Example3::project(Vector3d point) {

    //Orthognal Project
    //Vector2d projected_point(point.get_x() * fov_factor,point.get_y()*fov_factor);
    //
    //Perspective Project
    Vector2d projected_point(
                             fov_factor * point.get_x() / point.get_z(),
                             fov_factor * point.get_y() / point.get_z()
                             );
    return projected_point;
}


