#pragma once

#include <stdint.h>
class SDL_Renderer;
class SDL_Texture;

class Example {
public:
    Example();
    virtual ~Example();
    virtual void initialize() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
    virtual void process_input()=0;
    virtual void setWindowSize(int width,int height);
    virtual void setSDLRenderer(SDL_Renderer* renderer);
    virtual void setColorBuffer(uint32_t* buffer);
    virtual void setColorBufferTexture(SDL_Texture* texture);
    virtual void clear_color_buffer(uint32_t color); 
    virtual void setup_render();
    virtual void clear_render();
protected:
    SDL_Renderer* m_renderer;

    int screen_width;
    int screen_height;

    uint32_t* color_buffer = nullptr;
    SDL_Texture* color_buffer_texture = nullptr;
};
