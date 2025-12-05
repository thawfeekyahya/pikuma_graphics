#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include "util.h"
#include "example.h"

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
     void initialize();
     void destroy_window();

     void attach(Example* example);
private:
    void process_input();
    void render_color_buffer();
    int previous_frame_time = 0;

    bool m_isRunning = false;
    uint screen_width = 800;
    uint screen_height = 600;
    uint32_t* color_buffer = nullptr;
    SDL_Texture* color_buffer_texture = nullptr;

    Example* m_example = nullptr;
};
