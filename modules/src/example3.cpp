#include <iostream>
#include "example3.h"
#include "util.h"


using namespace std;
using namespace pikuma::utility;

void Example3::initialize() {
   std::cout<<"Initialize Example 3"<<std::endl;
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
    
}

void Example3::render() {
    setup_render();    


    clear_render();
}

void Example3::process_input() {
   std::cout<<"process_input Example 3"<<std::endl;
}


Vector2d Example3::project(Vector3d point) {
    float fov_factor = 640;
    Vector2d projected_point(
                             fov_factor * point.get_x() / point.get_z(),
                             fov_factor * point.get_y() / point.get_z()
                             );
    return projected_point;
}


