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

class SdlWindow {
public:
    explicit SdlWindow(WindowConfig config = {});
    ~SdlWindow();

    [[nodiscard]] bool isRunning() const noexcept;
    void setup();
    void update();
    void initialize();
    void destroy_window();

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
    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;
    SDL_Texture* m_colorBufferTexture = nullptr;

    std::unique_ptr<Example> m_example;
};
