#pragma once

#include <cstdint>
#include <vector>

namespace pikuma {

// Colors are 32-bit ARGB (0xAARRGGBB).
using Color = std::uint32_t;

inline constexpr Color kBlack = 0xFF000000;
inline constexpr Color kWhite = 0xFFFFFFFF;
inline constexpr Color kRed = 0xFFFF0000;
inline constexpr Color kGreen = 0xFF00FF00;
inline constexpr Color kBlue = 0xFF0000FF;
inline constexpr Color kYellow = 0xFFFFFF00;

// The CPU-side pixel array we draw into each frame. The window copies it to the screen.
// It does not use SDL, so drawing code can be unit tested.
class ColorBuffer {
public:
    ColorBuffer() = default;
    ColorBuffer(int width, int height);

    void resize(int width, int height);
    void clear(Color color);

    // Ignores pixels outside the buffer, so callers do not need to clip.
    void set_pixel(int x, int y, Color color);
    [[nodiscard]] Color pixel(int x, int y) const;

    [[nodiscard]] int width() const noexcept { return m_width; }
    [[nodiscard]] int height() const noexcept { return m_height; }
    [[nodiscard]] bool contains(int x, int y) const noexcept {
        return x >= 0 && x < m_width && y >= 0 && y < m_height;
    }

    [[nodiscard]] const Color* data() const noexcept { return m_pixels.data(); }
    [[nodiscard]] int pitch_bytes() const noexcept { return m_width * static_cast<int>(sizeof(Color)); }

private:
    int m_width = 0;
    int m_height = 0;
    std::vector<Color> m_pixels;
};

}  // namespace pikuma
