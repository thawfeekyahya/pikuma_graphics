#include "sdlwindow.h"

#include <iostream>
#include <SDL2/SDL.h>

using namespace std;


void SdlWindow::setup() {
    uint total_len = screen_width * screen_height;
    color_buffer = new uint32_t[total_len];
}

SdlWindow::~SdlWindow() {
    destroy_window();
}

void SdlWindow::destroy_window() {
    delete color_buffer;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void SdlWindow::initialize() {
    
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        cout<<"Error"<<endl;
    } else {
        cout<<"Success"<<endl;
    }

    //Create SDL window
    window = SDL_CreateWindow(NULL,SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              screen_width,screen_height,      
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

    //Initialize the texture
    color_buffer_texture = SDL_CreateTexture(renderer,
                                             SDL_PIXELFORMAT_ARGB8888,
                                             SDL_TEXTUREACCESS_STREAMING,
                                             screen_width,
                                             screen_height);

}

void SdlWindow::render_color_buffer () {
    SDL_UpdateTexture(
        color_buffer_texture,
        nullptr,
        color_buffer,
        screen_width * sizeof(uint32_t)
    );

    SDL_RenderCopy(renderer,color_buffer_texture,nullptr,nullptr);
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


void SdlWindow::clear_color_buffer(uint32_t color) {
    for (uint y=0; y < screen_height; y++) {
        for (uint x=0; x < screen_width; x++) {
            color_buffer[(screen_width * y) + x] = color;
        }
    }
}

void SdlWindow::render() {
    SDL_SetRenderDrawColor(renderer,255,0,0,255);
    SDL_RenderClear(renderer);

    render_color_buffer();
    clear_color_buffer(0xFFFFFF00);

    SDL_RenderPresent(renderer);
}
