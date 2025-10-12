#include "sdlwindow.h"

#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

void SdlWindow::setup() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        cout<<"Error"<<endl;
    } else {
        cout<<"Success"<<endl;
    }

    //Create SDL window
    window = SDL_CreateWindow(NULL,SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              800,600,      
                              SDL_WINDOW_BORDERLESS);

    if (window == nullptr) {
        cout<<"Error creating SDL window"<<endl;
        m_isRunning = false;
    }

    //Create SDL Renderer
    renderer = SDL_CreateRenderer(window,-1,0);

    if (renderer == nullptr) {
        cout<<"Error creating SDL Renderer"<<endl;
        m_isRunning = false;
    }

    m_isRunning = true;
}



bool SdlWindow::isRunning() const {
    return m_isRunning;
}

void SdlWindow::update() {
}


void SdlWindow::process_input() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            m_isRunning = false;
        break;

        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                m_isRunning = false;
            }
       break;

    }
}

void SdlWindow::render() {
    SDL_SetRenderDrawColor(renderer,255,0,0,255);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
}
