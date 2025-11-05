#pragma once


#include "example.h"
#include <SDL2/SDL.h>

class Example2 : public Example {
public:
    Example2() = default;
    void initialize() override;
    void update() override;
    void render() override;
    void process_input() override;
    void setWindowSize(int width,int height) override;
    void setSDLRenderer(SDL_Renderer* renderer) override;
    void setColorBuffer(uint32_t* buffer) override;
    void setColorBufferTexture(SDL_Texture* buffer) override;
private:
    // Window / initialize Settings
    SDL_Renderer* m_renderer;

    int screen_width;
    int screen_height;

    uint32_t* color_buffer = nullptr;
    SDL_Texture* color_buffer_texture = nullptr;

    void clear_color_buffer(uint32_t color);

    void draw_pixel(int x,int y, uint32_t color);
    void draw_rectangle(uint x,uint y,uint width,uint height,uint32_t color);
};
