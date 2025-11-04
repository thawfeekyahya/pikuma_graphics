#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include "util.h"
#include "triangle.h"
#include "example.h"
#include "mesh.h"

#define FPS 30
#define FRAME_TARGET_TIME (1000 / FPS)

class SdlWindow {
public:
     SdlWindow()=default;
     ~SdlWindow();
     SDL_Window* window;
     SDL_Renderer* renderer;
     bool isRunning() const;
     void setup();
     void update();
     void render();
     void initialize();
     void destroy_window();
     pikuma::utility::Vector2d project(pikuma::utility::Vector3d point);

     void attach(Example* example);
private:
    void process_input();
    void clear_color_buffer(uint32_t color);
    void render_color_buffer();
    void populate_dot_array_cube();
    void populate_cube_vertices();
    void draw_grid();
    void draw_pixel(int x,int y, uint32_t color);
    void draw_rectangle(uint x,uint y,uint width,uint height,uint32_t color);
    int previous_frame_time = 0;

    bool m_isRunning = false;
    uint screen_width = 800;
    uint screen_height = 600;
    uint32_t* color_buffer = nullptr;
    SDL_Texture* color_buffer_texture = nullptr;

    static constexpr int N_POINTS = 9*9*9;

    pikuma::utility::Vector3d cube_points[N_POINTS];
    pikuma::utility::Vector2d projected_points[N_POINTS];
    pikuma::utility::Vector3d cube_rotation{0.01,0.01,0.01};

    std::vector<Triangle> triangles_to_render{N_MESH_VERTICES};

    Example* m_example = nullptr;

};
