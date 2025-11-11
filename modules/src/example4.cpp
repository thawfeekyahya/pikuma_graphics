#include "example4.h"
#include <iostream>
#include "util.h"

void Example4::initialize() {
}


Example4::Example4():
    cube_vertices {
         {-1,-1,-1},
         {-1, 1,-1},
         { 1, 1,-1},
         { 1,-1,-1}, 
         { 1, 1, 1},
         { 1,-1, 1},
         {-1, 1, 1},
         {-1,-1, 1}
    },
    cube_faces {
        {1,2,3},
        {1,3,4},

        {4,3,5},
        {4,5,6},

        {6,5,7},
        {6,7,8},

        {8,7,2},
        {8,2,1},

        {2,7,5},
        {2,5,3},

        {6,8,1},
        {6,1,4}
    }
{
   std::cout<<"Example4 - Draw vertex and triangles"<<std::endl;
}


void Example4::update() {
}

void Example4::render() {
}

void Example4::process_input() {
}
