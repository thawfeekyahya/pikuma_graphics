#include "pikuma/sdl_window.h"

#include <iostream>
#include <string>

namespace pikuma {

SdlWindow::SdlWindow(WindowConfig config) : m_config(config) {}

SdlWindow::~SdlWindow() {
    m_color_buffer_texture.reset();
    m_renderer.reset();
    m_window.reset();
    if (m_sdl_initialized) {
        SDL_Quit();
    }
}

bool SdlWindow::initialize() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << '\n';
        return false;
    }
    m_sdl_initialized = true;

    if (m_config.fullscreen) {
        SDL_DisplayMode display_mode{};
        if (SDL_GetCurrentDisplayMode(0, &display_mode) == 0) {
            m_config.width = display_mode.w;
            m_config.height = display_mode.h;
        } else {
            std::cerr << "Failed to query display mode, using " << m_config.width << 'x' << m_config.height << '\n';
        }
    }

    Uint32 window_flags = SDL_WINDOW_SHOWN;
    if (m_config.borderless) {
        window_flags |= SDL_WINDOW_BORDERLESS;
    }

    m_window.reset(SDL_CreateWindow("Pikuma 3D Graphics", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                    m_config.width, m_config.height, window_flags));
    if (!m_window) {
        std::cerr << "Error creating SDL window: " << SDL_GetError() << '\n';
        return false;
    }

    m_renderer.reset(SDL_CreateRenderer(m_window.get(), -1, SDL_RENDERER_ACCELERATED));
    if (!m_renderer) {
        std::cerr << "Error creating SDL renderer: " << SDL_GetError() << '\n';
        return false;
    }

    m_color_buffer_texture.reset(SDL_CreateTexture(m_renderer.get(), SDL_PIXELFORMAT_ARGB8888,
                                                   SDL_TEXTUREACCESS_STREAMING, m_config.width, m_config.height));
    if (!m_color_buffer_texture) {
        std::cerr << "Error creating SDL texture: " << SDL_GetError() << '\n';
        return false;
    }

    if (m_config.fullscreen) {
        SDL_SetWindowFullscreen(m_window.get(), SDL_WINDOW_FULLSCREEN_DESKTOP);
    }

    m_color_buffer.resize(m_config.width, m_config.height);
    m_is_running = true;
    return true;
}

void SdlWindow::run(Example& example) {
    if (!m_is_running) {
        std::cerr << "SdlWindow::run called before a successful initialize()\n";
        return;
    }

    const std::string title(example.title());
    std::cout << title << '\n';
    SDL_SetWindowTitle(m_window.get(), title.c_str());

    example.setup(m_config.width, m_config.height);

    while (m_is_running) {
        wait_for_next_frame();

        process_input(example);
        if (!m_is_running) {
            break;
        }

        example.update();

        m_color_buffer.clear(kBlack);
        example.render(m_color_buffer);
        present();
    }
}

void SdlWindow::wait_for_next_frame() {
    const Uint32 frame_target_time_ms = 1000U / static_cast<Uint32>(m_config.target_fps);
    const Uint32 elapsed = SDL_GetTicks() - m_previous_frame_time;
    if (elapsed < frame_target_time_ms) {
        SDL_Delay(frame_target_time_ms - elapsed);
    }
    m_previous_frame_time = SDL_GetTicks();
}

void SdlWindow::process_input(Example& example) {
    SDL_Event event{};
    while (SDL_PollEvent(&event) != 0) {
        switch (event.type) {
            case SDL_QUIT:
                m_is_running = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    m_is_running = false;
                } else {
                    example.on_key_down(event.key.keysym.sym);
                }
                break;
            default:
                break;
        }
    }
}

void SdlWindow::present() {
    SDL_UpdateTexture(m_color_buffer_texture.get(), nullptr, m_color_buffer.data(), m_color_buffer.pitch_bytes());
    SDL_RenderCopy(m_renderer.get(), m_color_buffer_texture.get(), nullptr, nullptr);
    SDL_RenderPresent(m_renderer.get());
}

}  // namespace pikuma
