#pragma once

#include <cstdint>

class SDL_Renderer;
class SDL_Texture;

class Example {
public:
    Example() = default;
    virtual ~Example() = default;

    virtual void initialize();
    virtual void update() = 0;
    virtual void render() = 0;
    virtual void process_input() = 0;

    virtual void setWindowSize(int width, int height);
    virtual void setSDLRenderer(SDL_Renderer* renderer);
    virtual void setColorBuffer(std::uint32_t* buffer);
    virtual void setColorBufferTexture(SDL_Texture* texture);
    virtual void clear_color_buffer(std::uint32_t color);
    virtual void setup_render();
    virtual void clear_render();

protected:
    SDL_Renderer* m_renderer = nullptr;

    int screen_width = 800;
    int screen_height = 600;

    std::uint32_t* color_buffer = nullptr;
    SDL_Texture* color_buffer_texture = nullptr;
};
