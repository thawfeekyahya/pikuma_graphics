#pragma once

#include "example3.h"
#include "util.h"
#include <vector>

class Example5: public Example3 {
public:
    Example5();
    void initialize() override;
    void update() override;
    void render() override;
    void process_input() override;

    static constexpr int CUBE_VERTICES=8;
    static constexpr int CUBE_FACES=6*2;

    std::array<pikuma::utility::Vector3d,CUBE_VERTICES> cube_vertices = {{
        {-1,-1,-1},
        {-1, 1,-1},
        {1 , 1,-1},
        {1 ,-1,-1},
        {1 , 1, 1},
        {1 ,-1, 1},
        {-1, 1, 1},
        {-1,-1, 1}
    }};

    std::array<pikuma::utility::Face,CUBE_FACES> cube_faces = {{
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
    std::vector<pikuma::utility::Triangle> triangles_to_render;

    //----Example -5
    pikuma::utility::Mesh cube_mesh;
    void loadCubeMesData();


protected:
    void draw_line(int x0,int x1,int y0,int y1,uint32_t color);
    void draw_triangle(int x0,int y0,int x1,int y1,int x2, int y2,uint32_t color);
};

