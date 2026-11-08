#include "pikuma/draw.h"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <utility>

namespace pikuma {

namespace {

int to_int(float value) {
    return static_cast<int>(value);
}

// Triangle with a flat bottom edge: (x1,y1) and (x2,y2) share the same y, below (x0,y0).
void fill_flat_bottom_triangle(ColorBuffer& buffer, int x0, int y0, int x1, int y1, int x2, int y2, Color color) {
    // Inverse slopes of the two legs
    const float inv_slope_1 = static_cast<float>(x1 - x0) / static_cast<float>(y1 - y0);
    const float inv_slope_2 = static_cast<float>(x2 - x0) / static_cast<float>(y2 - y0);

    // Start from the top vertex (x0,y0)
    float x_start = static_cast<float>(x0);
    float x_end = static_cast<float>(x0);

    // Scanlines from top to bottom
    for (int y = y0; y <= y2; ++y) {
        draw_line(buffer, to_int(x_start), y, to_int(x_end), y, color);
        x_start += inv_slope_1;
        x_end += inv_slope_2;
    }
}

// Triangle with a flat top edge: (x0,y0) and (x1,y1) share the same y, above (x2,y2).
void fill_flat_top_triangle(ColorBuffer& buffer, int x0, int y0, int x1, int y1, int x2, int y2, Color color) {
    // Inverse slopes of the two legs
    const float inv_slope_1 = static_cast<float>(x2 - x0) / static_cast<float>(y2 - y0);
    const float inv_slope_2 = static_cast<float>(x2 - x1) / static_cast<float>(y2 - y1);

    // Start from the bottom vertex (x2,y2)
    float x_start = static_cast<float>(x2);
    float x_end = static_cast<float>(x2);

    // Scanlines from bottom to top
    for (int y = y2; y >= y0; --y) {
        draw_line(buffer, to_int(x_start), y, to_int(x_end), y, color);
        x_start -= inv_slope_1;
        x_end -= inv_slope_2;
    }
}

}  // namespace

void draw_pixel(ColorBuffer& buffer, int x, int y, Color color) {
    buffer.set_pixel(x, y, color);
}

void draw_grid(ColorBuffer& buffer, int spacing, Color color) {
    if (spacing <= 0) {
        return;
    }
    for (int y = 0; y < buffer.height(); ++y) {
        for (int x = 0; x < buffer.width(); ++x) {
            if (x % spacing == 0 || y % spacing == 0) {
                draw_pixel(buffer, x, y, color);
            }
        }
    }
}

void draw_rect(ColorBuffer& buffer, int x, int y, int width, int height, Color color) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            draw_pixel(buffer, x + j, y + i, color);
        }
    }
}

void draw_line(ColorBuffer& buffer, int x0, int y0, int x1, int y1, Color color) {
    const int delta_x = x1 - x0;
    const int delta_y = y1 - y0;

    const int longest_side_length = std::max(std::abs(delta_x), std::abs(delta_y));

    if (longest_side_length == 0) {
        draw_pixel(buffer, x0, y0, color);
        return;
    }

    // How far to step in x and y for each pixel
    const float x_inc = static_cast<float>(delta_x) / static_cast<float>(longest_side_length);
    const float y_inc = static_cast<float>(delta_y) / static_cast<float>(longest_side_length);

    float current_x = static_cast<float>(x0);
    float current_y = static_cast<float>(y0);

    for (int i = 0; i <= longest_side_length; ++i) {
        draw_pixel(buffer, static_cast<int>(std::round(current_x)), static_cast<int>(std::round(current_y)), color);
        current_x += x_inc;
        current_y += y_inc;
    }
}

void draw_triangle(ColorBuffer& buffer, int x0, int y0, int x1, int y1, int x2, int y2, Color color) {
    draw_line(buffer, x0, y0, x1, y1, color);
    draw_line(buffer, x1, y1, x2, y2, color);
    draw_line(buffer, x2, y2, x0, y0, color);
}

void draw_triangle(ColorBuffer& buffer, const Triangle& triangle, Color color) {
    const auto& [a, b, c] = triangle.points;
    draw_triangle(buffer, to_int(a.x), to_int(a.y), to_int(b.x), to_int(b.y), to_int(c.x), to_int(c.y), color);
}

void draw_filled_triangle(ColorBuffer& buffer, int x0, int y0, int x1, int y1, int x2, int y2, Color color) {
    // Sort the vertices by y, top to bottom (y0 <= y1 <= y2)
    if (y0 > y1) {
        std::swap(y0, y1);
        std::swap(x0, x1);
    }
    if (y1 > y2) {
        std::swap(y1, y2);
        std::swap(x1, x2);
    }
    if (y0 > y1) {
        std::swap(y0, y1);
        std::swap(x0, x1);
    }

    if (y0 == y2) {
        // All three points on one row: the triangle has no height.
        // Stop here, since the slope math below would divide by zero.
        return;
    }

    if (y1 == y2) {
        fill_flat_bottom_triangle(buffer, x0, y0, x1, y1, x2, y2, color);
    } else if (y0 == y1) {
        fill_flat_top_triangle(buffer, x0, y0, x1, y1, x2, y2, color);
    } else {
        // Split at the middle vertex. Find (mx,my) on the long edge using similar triangles.
        const int my = y1;
        const int mx = (((x2 - x0) * (y1 - y0)) / (y2 - y0)) + x0;

        fill_flat_bottom_triangle(buffer, x0, y0, x1, y1, mx, my, color);
        fill_flat_top_triangle(buffer, x1, y1, mx, my, x2, y2, color);
    }
}

void draw_filled_triangle(ColorBuffer& buffer, const Triangle& triangle, Color color) {
    const auto& [a, b, c] = triangle.points;
    draw_filled_triangle(buffer, to_int(a.x), to_int(a.y), to_int(b.x), to_int(b.y), to_int(c.x), to_int(c.y), color);
}

}  // namespace pikuma
