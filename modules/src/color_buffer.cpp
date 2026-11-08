#include "pikuma/color_buffer.h"

#include <algorithm>
#include <cstddef>

namespace pikuma {

namespace {
std::size_t index_of(int x, int y, int width) {
    return (static_cast<std::size_t>(y) * static_cast<std::size_t>(width)) + static_cast<std::size_t>(x);
}
}  // namespace

ColorBuffer::ColorBuffer(int width, int height) {
    resize(width, height);
}

void ColorBuffer::resize(int width, int height) {
    m_width = std::max(width, 0);
    m_height = std::max(height, 0);
    m_pixels.assign(static_cast<std::size_t>(m_width) * static_cast<std::size_t>(m_height), kBlack);
}

void ColorBuffer::clear(Color color) {
    std::fill(m_pixels.begin(), m_pixels.end(), color);
}

void ColorBuffer::set_pixel(int x, int y, Color color) {
    if (contains(x, y)) {
        m_pixels[index_of(x, y, m_width)] = color;
    }
}

Color ColorBuffer::pixel(int x, int y) const {
    return contains(x, y) ? m_pixels[index_of(x, y, m_width)] : kBlack;
}

}  // namespace pikuma
