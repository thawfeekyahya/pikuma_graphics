#pragma once

#include "example.h"
#include <SDL2/SDL.h>

class Example1 : public Example {
public:
    Example1() = default;
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
    void draw_grid();


};
