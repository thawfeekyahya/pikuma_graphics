#include "example1.h"
#include <iostream>
#include <SDL2/SDL.h>

void Example1::initialize() {
   std::cout<<"Initialize Example 1"<<std::endl;
}

void Example1::update() {
    draw_grid();
}

void Example1::render() {
    SDL_SetRenderDrawColor(m_renderer,255,0,0,255);
    SDL_RenderClear(m_renderer);
    
    //code goes here

    SDL_UpdateTexture(
        color_buffer_texture,
        nullptr,
        color_buffer,
        screen_width * sizeof(uint32_t)
    );

    SDL_RenderCopy(m_renderer,color_buffer_texture,nullptr,nullptr);
    
    clear_color_buffer(0xFF000000);
    SDL_RenderPresent(m_renderer);
}



void Example1::clear_color_buffer(uint32_t color) {
    for (uint y=0; y < screen_height; y++) {
        for (uint x=0; x < screen_width; x++) {
            color_buffer[(screen_width * y) + x] = color;
        }
    }
}

void Example1::process_input() {
   std::cout<<"process_input Example 1"<<std::endl;
}

void Example1::setWindowSize(int width,int height) {
   screen_width = width;
   screen_height = height;
}

void Example1::setSDLRenderer(SDL_Renderer* renderer){
   m_renderer = renderer;
}

void Example1::setColorBuffer(uint32_t* buffer) {
    color_buffer = buffer;
}

void Example1::setColorBufferTexture(SDL_Texture* buffer) {
    color_buffer_texture = buffer;
}

void Example1::draw_grid() {
    int rowSize = 10;
    int colSize = 10;

    for (int y=0; y< screen_height; y++ ) {
        for (int x=0; x < screen_width; x++) {
             if ( x % rowSize == 0 || y % colSize == 0) {
                color_buffer[(screen_width * y) +x ] = 0xFFFF0000;
            }
        }
    }
}
