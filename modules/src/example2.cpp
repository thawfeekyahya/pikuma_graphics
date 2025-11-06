#include "example2.h"
#include <iostream>
#include <SDL2/SDL.h>

Example2::Example2() {
   initialize();
}

void Example2::update() {
    draw_rectangle(40,70,30,30,0xFF0000FF);
}

void Example2::render() {
    setup_render();
    //code goes here

    clear_render();
}

void Example2::initialize() {
   std::cout<<"Example2 - Draw Rectangle using Draw Pixel"<<std::endl;
}

void Example2::process_input() {
   std::cout<<"process_input Example 2"<<std::endl;
}

void Example2::draw_rectangle(uint x,uint y,uint width,uint height,uint32_t color){ 

    for (uint i=0; i < height; i++) {
        for (uint j=0; j < width; j++) {
            uint curr_x = x + j;
            uint curr_y = y + i;
            draw_pixel(curr_x,curr_y,color);
        }
    }
}

void Example2::draw_pixel(int x,int y, uint32_t color) {
    if ((x >=0 && x < screen_width) && (y >= 0 && y < screen_height)) {
        color_buffer[ screen_width * y + x ] = color;
    }
}
