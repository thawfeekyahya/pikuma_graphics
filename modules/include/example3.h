#pragma once
#include "example2.h"
#include "util.h"


class Example3 : public Example2 {
public:
    Example3();
    void initialize()override ;
    void update() override;
    void render() override;
    void process_input() override;
    void sdlEnterFrame();
private:
    static constexpr int N_POINTS = 9*9*9;
    pikuma::utility::Vector2d projected_points[N_POINTS];

    pikuma::utility::Vector3d cube_points[N_POINTS];
    void populate_dot_array_cube();

protected:
    pikuma::utility::Vector2d project(pikuma::utility::Vector3d point);
    pikuma::utility::Vector3d cube_rotation{0.01,0.01,0.01};
    pikuma::utility::Vector3d camera_pos{0.0,0.0,-5.0};
};
