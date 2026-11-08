#pragma once

#include <memory>

#include <SDL2/SDL.h>

#include "pikuma/color_buffer.h"
#include "pikuma/example.h"

namespace pikuma {

struct WindowConfig {
    int width = 800;  // replaced by the desktop size when `fullscreen` is set
    int height = 600;
    bool fullscreen = true;
    bool borderless = true;
    int target_fps = 30;
};

// Owns SDL, the window and the color buffer, and runs the main loop for an Example.
class SdlWindow {
public:
    explicit SdlWindow(WindowConfig config = {});
    ~SdlWindow();

    SdlWindow(const SdlWindow&) = delete;
    SdlWindow& operator=(const SdlWindow&) = delete;
    SdlWindow(SdlWindow&&) = delete;
    SdlWindow& operator=(SdlWindow&&) = delete;

    // Creates the window, renderer and texture. Returns false on failure.
    [[nodiscard]] bool initialize();

    // Runs the example until the window is closed or Escape is pressed.
    void run(Example& example);

    [[nodiscard]] bool is_running() const noexcept { return m_is_running; }

private:
    void wait_for_next_frame();
    void process_input(Example& example);
    void present();

    struct WindowDeleter {
        void operator()(SDL_Window* window) const noexcept { SDL_DestroyWindow(window); }
    };
    struct RendererDeleter {
        void operator()(SDL_Renderer* renderer) const noexcept { SDL_DestroyRenderer(renderer); }
    };
    struct TextureDeleter {
        void operator()(SDL_Texture* texture) const noexcept { SDL_DestroyTexture(texture); }
    };

    WindowConfig m_config;
    bool m_sdl_initialized = false;
    bool m_is_running = false;
    Uint32 m_previous_frame_time = 0;

    ColorBuffer m_color_buffer;

    // The destructor frees these in order: texture, renderer, window, then SDL_Quit().
    std::unique_ptr<SDL_Window, WindowDeleter> m_window;
    std::unique_ptr<SDL_Renderer, RendererDeleter> m_renderer;
    std::unique_ptr<SDL_Texture, TextureDeleter> m_color_buffer_texture;
};

}  // namespace pikuma
