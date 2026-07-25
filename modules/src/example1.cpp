#include "example1.h"

#include <iostream>

Example1::Example1() = default;

void Example1::initialize() {
    std::cout << "Example1 - Simple Grid rendering" << std::endl;
}

void Example1::update() {
    draw_grid();
}

void Example1::render() {
    setup_render();
    clear_render();
}

void Example1::process_input() {
    // Input handling can be extended by derived examples.
}

void Example1::draw_grid() {
    if (color_buffer == nullptr) {
        return;
    }

    constexpr int row_size = 10;
    constexpr int col_size = 10;

    for (int y = 0; y < screen_height; ++y) {
        for (int x = 0; x < screen_width; ++x) {
            if (x % row_size == 0 || y % col_size == 0) {
                color_buffer[(screen_width * y) + x] = 0xFFFF0000;
            }
        }
    }
}
