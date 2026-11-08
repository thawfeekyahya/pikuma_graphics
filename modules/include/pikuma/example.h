#pragma once

#include <string_view>

#include <SDL2/SDL_keycode.h>

#include "pikuma/color_buffer.h"

namespace pikuma {

// Base class for each step of the course.
//
// SdlWindow owns the window, the frame loop and the color buffer. Each frame it:
//   1. passes key presses to on_key_down()
//   2. calls update()
//   3. clears the color buffer, calls render(buffer), and shows the buffer on screen
//
// A new example only overrides what it needs: title() and render() are required.
class Example {
public:
    virtual ~Example() = default;

    Example(const Example&) = delete;
    Example& operator=(const Example&) = delete;
    Example(Example&&) = delete;
    Example& operator=(Example&&) = delete;

    // Shown in the window title and printed when the example starts.
    [[nodiscard]] virtual std::string_view title() const = 0;

    // Called once by SdlWindow, after the window size is known.
    void setup(int window_width, int window_height) {
        m_window_width = window_width;
        m_window_height = window_height;
        on_setup();
    }

    virtual void on_key_down(SDL_Keycode /*key*/) {}
    virtual void update() {}
    virtual void render(ColorBuffer& buffer) = 0;

protected:
    Example() = default;

    // Override for one-time setup such as loading meshes.
    virtual void on_setup() {}

    [[nodiscard]] int window_width() const noexcept { return m_window_width; }
    [[nodiscard]] int window_height() const noexcept { return m_window_height; }

private:
    int m_window_width = 0;
    int m_window_height = 0;
};

}  // namespace pikuma
