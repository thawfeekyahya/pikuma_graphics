#pragma once

// Drawing functions, the same as display.c / triangle.c in the course code.
// They are free functions that take the buffer to draw into, instead of using a
// global color_buffer.

#include "pikuma/color_buffer.h"
#include "pikuma/triangle.h"

namespace pikuma {

void draw_pixel(ColorBuffer& buffer, int x, int y, Color color);

void draw_grid(ColorBuffer& buffer, int spacing, Color color);

void draw_rect(ColorBuffer& buffer, int x, int y, int width, int height, Color color);

// DDA line algorithm.
void draw_line(ColorBuffer& buffer, int x0, int y0, int x1, int y1, Color color);

// Wireframe triangle (three lines).
void draw_triangle(ColorBuffer& buffer, int x0, int y0, int x1, int y1, int x2, int y2, Color color);
void draw_triangle(ColorBuffer& buffer, const Triangle& triangle, Color color);

// Solid triangle, filled with the flat-bottom / flat-top method.
void draw_filled_triangle(ColorBuffer& buffer, int x0, int y0, int x1, int y1, int x2, int y2, Color color);
void draw_filled_triangle(ColorBuffer& buffer, const Triangle& triangle, Color color);

}  // namespace pikuma
