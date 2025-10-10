#include "sdlwindow.h"

#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

SdlWindow::SdlWindow() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        cout<<"Error"<<endl;
    } else {
        cout<<"Success"<<endl;
    }
}
