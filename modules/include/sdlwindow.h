#pragma once

#include <iostream>
#include <SDL2/SDL.h>

class SdlWindow {
public:
     SdlWindow();
     SDL_Window* window;
     SDL_Renderer* renderer;
     bool isRunning() const;
private:
     bool m_isRunning = false;

};
