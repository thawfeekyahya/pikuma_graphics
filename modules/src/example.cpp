#include "example.h"

#include <SDL2/SDL.h>

void Example::initialize() {}

void Example::setWindowSize(int width, int height) {
    screen_width = width;
    screen_height = height;
}

void Example::setSDLRenderer(SDL_Renderer* renderer) {
    m_renderer = renderer;
}

void Example::setColorBuffer(std::uint32_t* buffer) {
    color_buffer = buffer;
}

void Example::setColorBufferTexture(SDL_Texture* texture) {
    color_buffer_texture = texture;
}

void Example::clear_color_buffer(std::uint32_t color) {
    if (color_buffer == nullptr) {
        return;
    }

    for (int y = 0; y < screen_height; ++y) {
        for (int x = 0; x < screen_width; ++x) {
            color_buffer[(screen_width * y) + x] = color;
        }
    }
}

void Example::setup_render() {
    if (m_renderer == nullptr) {
        return;
    }

    SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
    SDL_RenderClear(m_renderer);
}

void Example::clear_render() {
    if (m_renderer == nullptr || color_buffer == nullptr || color_buffer_texture == nullptr) {
        return;
    }

    SDL_UpdateTexture(
        color_buffer_texture,
        nullptr,
        color_buffer,
        screen_width * static_cast<int>(sizeof(std::uint32_t)));

    SDL_RenderCopy(m_renderer, color_buffer_texture, nullptr, nullptr);

    clear_color_buffer(0xFF000000);
    SDL_RenderPresent(m_renderer);
}
