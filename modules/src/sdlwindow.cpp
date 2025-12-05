#include "sdlwindow.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include "util.h"
#include "example.h"

using namespace std;
using namespace pikuma::utility;

void SdlWindow::attach(Example* example) {
    m_example = example;
    m_example->setWindowSize(screen_width,screen_height);
    m_example->setSDLRenderer(renderer);
    m_example->setColorBuffer(color_buffer);
    m_example->setColorBufferTexture(color_buffer_texture);
}

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


    //Query window max size
    SDL_DisplayMode display_mode;
    SDL_GetCurrentDisplayMode(0,&display_mode);

    screen_width = display_mode.w;
    screen_height = display_mode.h;

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

    //Initialize the texture
    color_buffer_texture = SDL_CreateTexture(renderer,
                                             SDL_PIXELFORMAT_ARGB8888,
                                             SDL_TEXTUREACCESS_STREAMING,
                                             screen_width,
                                             screen_height);

    SDL_SetWindowFullscreen(window,SDL_WINDOW_FULLSCREEN);

    m_isRunning = true;
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

    if (!m_example) {
        std::cout<<"Example Cannot be Null "<<std::endl;
        return;
    }


    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks()- previous_frame_time);   
    previous_frame_time = SDL_GetTicks();


    //Save CPU cycles by delaying update as per frame rate
    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
        SDL_Delay(time_to_wait);
    }

    process_input();
    m_example->update();
    m_example->render();
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
