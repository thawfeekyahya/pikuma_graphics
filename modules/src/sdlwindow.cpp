#include "sdlwindow.h"

#include <iostream>
#include <utility>

SdlWindow::SdlWindow(WindowConfig config) : m_config(std::move(config)) {}

void SdlWindow::attach(std::unique_ptr<Example> example) {
    m_example = std::move(example);
    if (!m_example) {
        return;
    }

    m_example->setWindowSize(m_config.width, m_config.height);
    m_example->setSDLRenderer(m_renderer);
    m_example->setColorBuffer(m_colorBuffer.data());
    m_example->setColorBufferTexture(m_colorBufferTexture);
}

void SdlWindow::setup() {
    const std::size_t total_len = static_cast<std::size_t>(m_config.width) * static_cast<std::size_t>(m_config.height);
    m_colorBuffer.assign(total_len, 0xFF000000);
}

SdlWindow::~SdlWindow() {
    destroy_window();
}

void SdlWindow::destroy_window() {
    if (m_colorBufferTexture != nullptr) {
        SDL_DestroyTexture(m_colorBufferTexture);
        m_colorBufferTexture = nullptr;
    }

    if (m_renderer != nullptr) {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }

    if (m_window != nullptr) {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }

    SDL_Quit();
}

void SdlWindow::initialize() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Failed to initialize SDL" << std::endl;
        m_isRunning = false;
        return;
    }

    SDL_DisplayMode display_mode{};
    if (SDL_GetCurrentDisplayMode(0, &display_mode) != 0) {
        std::cerr << "Failed to query display mode" << std::endl;
        m_config.width = 800;
        m_config.height = 600;
    } else {
        m_config.width = display_mode.w;
        m_config.height = display_mode.h;
    }

    Uint32 window_flags = SDL_WINDOW_SHOWN;
    if (m_config.borderless) {
        window_flags |= SDL_WINDOW_BORDERLESS;
    }

    m_window = SDL_CreateWindow(
        "Pikuma 3D Graphics",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        m_config.width,
        m_config.height,
        window_flags);

    if (m_window == nullptr) {
        std::cerr << "Error creating SDL window" << std::endl;
        m_isRunning = false;
        return;
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if (m_renderer == nullptr) {
        std::cerr << "Error creating SDL renderer" << std::endl;
        m_isRunning = false;
        return;
    }

    m_colorBufferTexture = SDL_CreateTexture(
        m_renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        m_config.width,
        m_config.height);

    if (m_colorBufferTexture == nullptr) {
        std::cerr << "Error creating SDL texture" << std::endl;
        m_isRunning = false;
        return;
    }

    if (m_config.fullscreen) {
        SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    }

    setup();
    m_isRunning = true;
}

void SdlWindow::render_color_buffer() {
    if (m_colorBufferTexture == nullptr || m_renderer == nullptr) {
        return;
    }

    SDL_UpdateTexture(
        m_colorBufferTexture,
        nullptr,
        m_colorBuffer.data(),
        m_config.width * static_cast<int>(sizeof(std::uint32_t)));

    SDL_RenderCopy(m_renderer, m_colorBufferTexture, nullptr, nullptr);
}

bool SdlWindow::isRunning() const noexcept {
    return m_isRunning;
}

void SdlWindow::update() {
    if (!m_example) {
        std::cerr << "Example cannot be null" << std::endl;
        m_isRunning = false;
        return;
    }

    const int elapsed = SDL_GetTicks() - previous_frame_time;
    int time_to_wait = FRAME_TARGET_TIME_MS - elapsed;
    previous_frame_time = SDL_GetTicks();

    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME_MS) {
        SDL_Delay(static_cast<Uint32>(time_to_wait));
    }

    process_input();
    if (!m_isRunning) {
        return;
    }

    m_example->process_input();
    m_example->update();
    m_example->render();
}

void SdlWindow::process_input() {
    SDL_Event event{};
    while (SDL_PollEvent(&event) != 0) {
        switch (event.type) {
            case SDL_QUIT:
                m_isRunning = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    m_isRunning = false;
                }
                break;
            default:
                break;
        }
    }
}
