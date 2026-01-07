#pragma once

#include "example3.h"
#include "util.h"
#include <vector>
#include <string>

class Example6: public Example3 {
public:
    Example6();
    void initialize() override;
    void update() override;
    void render() override;
    void process_input() override;

    static constexpr int CUBE_VERTICES=8;
    static constexpr int CUBE_FACES=6*2;

private:
    pikuma::utility::Vector3d camera_pos{0.0,0.0,0.0};
    pikuma::utility::Vector3d cube_rotation{0.01,0.01,0.01};
    std::vector<pikuma::utility::Triangle> triangles_to_render;

    //example 6
    pikuma::utility::Mesh cube_mesh;


protected:
    void draw_line(int x0,int x1,int y0,int y1,uint32_t color);
    void draw_triangle(int x0,int y0,int x1,int y1,int x2, int y2,uint32_t color);
    //example 6
    void load_obj_data(const std::string& path);

};

