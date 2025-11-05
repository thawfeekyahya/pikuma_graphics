#pragma once


#include "example.h"
#include <SDL2/SDL.h>

class Example2 : public Example {
public:
    Example2();
    void initialize() override;
    void update() override;
    void render() override;
    void process_input() override;
protected:
    void draw_pixel(int x,int y, uint32_t color);
    void draw_rectangle(uint x,uint y,uint width,uint height,uint32_t color);
};
