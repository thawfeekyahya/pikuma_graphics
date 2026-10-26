#pragma once

#include <cstdint>
#include <memory>
#include <vector>

#include <SDL2/SDL.h>

#include "example.h"

constexpr int FPS = 30;
constexpr int FRAME_TARGET_TIME_MS = 1000 / FPS;

struct WindowConfig {
    int width = 800;
    int height = 600;
    bool fullscreen = true;
    bool borderless = true;
};

namespace detail {
struct SdlWindowDeleter {
    void operator()(SDL_Window* window) const noexcept {
        if (window != nullptr) {
            SDL_DestroyWindow(window);
        }
    }
};

struct SdlRendererDeleter {
    void operator()(SDL_Renderer* renderer) const noexcept {
        if (renderer != nullptr) {
            SDL_DestroyRenderer(renderer);
        }
    }
};

struct SdlTextureDeleter {
    void operator()(SDL_Texture* texture) const noexcept {
        if (texture != nullptr) {
            SDL_DestroyTexture(texture);
        }
    }
};
}  // namespace detail

class SdlWindow {
public:
    explicit SdlWindow(WindowConfig config = {});
    ~SdlWindow();

    [[nodiscard]] bool isRunning() const noexcept;
    void setup();
    void update();
    bool initialize();
    void destroy_window() noexcept;

    void attach(std::unique_ptr<Example> example);

    enum class RENDER_MODE {
        RENDER_WIRE,
        RENDER_WIRE_VERTEX,
        RENDER_FILL_TRIANGLE,
        RENDER_FILL_TRIANGLE_WIRE
    };

private:
    void process_input();
    void render_color_buffer();

    int previous_frame_time = 0;

    bool m_isRunning = false;
    bool m_isCullingEnabled = false;
    RENDER_MODE m_renderMode = RENDER_MODE::RENDER_WIRE;
    WindowConfig m_config;
    std::vector<std::uint32_t> m_colorBuffer;
    std::unique_ptr<SDL_Window, detail::SdlWindowDeleter> m_window;
    std::unique_ptr<SDL_Renderer, detail::SdlRendererDeleter> m_renderer;
    std::unique_ptr<SDL_Texture, detail::SdlTextureDeleter> m_colorBufferTexture;

    std::unique_ptr<Example> m_example;
};
