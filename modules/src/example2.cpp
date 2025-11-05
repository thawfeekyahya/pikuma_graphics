#include "example2.h"
#include <iostream>
#include <SDL2/SDL.h>

void Example2::initialize() {
   std::cout<<"Initialize Example 2"<<std::endl;
}

void Example2::update() {
    draw_rectangle(40,70,30,30,0xFF0000FF);
}

void Example2::render() {
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



void Example2::clear_color_buffer(uint32_t color) {
    for (uint y=0; y < screen_height; y++) {
        for (uint x=0; x < screen_width; x++) {
            color_buffer[(screen_width * y) + x] = color;
        }
    }
}

void Example2::process_input() {
   std::cout<<"process_input Example 2"<<std::endl;
}

void Example2::setWindowSize(int width,int height) {
   screen_width = width;
   screen_height = height;
}

void Example2::setSDLRenderer(SDL_Renderer* renderer){
   m_renderer = renderer;
}

void Example2::setColorBuffer(uint32_t* buffer) {
    color_buffer = buffer;
}

void Example2::setColorBufferTexture(SDL_Texture* buffer) {
    color_buffer_texture = buffer;
}

void Example2::draw_rectangle(uint x,uint y,uint width,uint height,uint32_t color){ 

    for (uint i=0; i < height; i++) {
        for (uint j=0; j < width; j++) {
            uint curr_x = x + j;
            uint curr_y = y + i;
            draw_pixel(curr_x,curr_y,color);
        }
    }
}

void Example2::draw_pixel(int x,int y, uint32_t color) {
    if ((x >=0 && x < screen_width) && (y >= 0 && y < screen_height)) {
        color_buffer[ screen_width * y + x ] = color;
    }
}
