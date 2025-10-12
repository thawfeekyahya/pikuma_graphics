#pragma once

#include <iostream>
#include <SDL2/SDL.h>

class SdlWindow {
public:
     SdlWindow()=default;
     SDL_Window* window;
     SDL_Renderer* renderer;
     bool isRunning() const;
     void setup();
     void update();
     void render();
     void process_input();
private:
    bool m_isRunning = false;

};
