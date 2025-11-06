#include "example.h"
#include <SDL2/SDL.h>

Example::Example() = default;
Example::~Example() = default; 

void Example::initialize() {
}

void Example::setWindowSize(int width,int height) {
   screen_width = width;
   screen_height = height;
}

void Example::setSDLRenderer(SDL_Renderer* renderer) {
   m_renderer = renderer;
}

void Example::setColorBuffer(uint32_t* buffer) {
    color_buffer = buffer;
}

void Example::setColorBufferTexture(SDL_Texture* texture){
    color_buffer_texture = texture;
}


void Example::clear_color_buffer(uint32_t color) {
    for (int y=0; y < screen_height; y++) {
        for (int x=0; x < screen_width; x++) {
            color_buffer[(screen_width * y) + x] = color;
        }
    }
}

void Example::setup_render() {
    SDL_SetRenderDrawColor(m_renderer,255,0,0,255);
    SDL_RenderClear(m_renderer);
}

void Example::clear_render() {
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
