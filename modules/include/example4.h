#pragma once

#include "example3.h"
#include "util.h"
#include <vector>

class Example4: public Example3 {
public:
    Example4();
    void initialize() override;
    void update() override;
    void render() override;
    void process_input() override;

    static constexpr int MESH_VERTICES=8;
    static constexpr int MESH_FACES=6*2;

    std::array<pikuma::utility::Vector3d,MESH_VERTICES> mesh_vertices = {{
        {-1,-1,-1},        
        {-1, 1,-1},        
        {1 , 1,-1},        
        {1 ,-1,-1},        
        {1 , 1, 1},        
        {1 ,-1, 1},        
        {-1, 1, 1},        
        {-1,-1, 1}        
    }};

    std::array<pikuma::utility::Face,MESH_FACES> mesh_faces = {{
        //Front
        {1,2,3},
        {1,3,4},
        //Right
        {4,3,5},
        {4,5,6},
        //Back
        {6,5,7},
        {6,7,8},
        //Left
        {8,7,2},
        {8,2,1},
        //Top
        {2,7,5},
        {2,5,3},
        //Bottom
        {6,8,1},
        {6,1,4}
    }};
private:
    pikuma::utility::Vector3d camera_pos{0.0,0.0,-5.0};
    pikuma::utility::Vector3d cube_rotation{0.01,0.01,0.01};
    std::array<pikuma::utility::Triangle,MESH_FACES> triangles_to_render;
};

