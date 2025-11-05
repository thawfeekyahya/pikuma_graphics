#include "example1.h"
#include <iostream>
#include <SDL2/SDL.h>

void Example1::initialize() {
   std::cout<<"Initialize Example 1"<<std::endl;
}

void Example1::update() {
    draw_grid();
}

void Example1::render() {
    setup_render();    
    //code goes here
    clear_render();
}

void Example1::process_input() {
   std::cout<<"process_input Example 1"<<std::endl;
}

void Example1::draw_grid() {
    int rowSize = 10;
    int colSize = 10;

    for (int y=0; y< screen_height; y++ ) {
        for (int x=0; x < screen_width; x++) {
             if ( x % rowSize == 0 || y % colSize == 0) {
                color_buffer[(screen_width * y) +x ] = 0xFFFF0000;
            }
        }
    }
}
