#pragma once

#include <iostream>
#include <SDL2/SDL.h>

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
     void process_input();
     void initialize();
     void destroy_window();
private:
    void clear_color_buffer(uint32_t color);
    void render_color_buffer();
    void draw_grid();
    void draw_pixel(uint x,uint y, uint32_t color);
    void draw_rectangle(uint x,uint y,uint width,uint height,uint32_t color);
    bool m_isRunning = false;
    uint screen_width = 800;
    uint screen_height = 600;
    uint32_t* color_buffer = nullptr;
    SDL_Texture* color_buffer_texture = nullptr;


};
