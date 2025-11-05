#pragma once

#include "example.h"
#include <SDL2/SDL.h>

class Example1 : public Example {
public:
    Example1() = default;
    void initialize() override;
    void update() override;
    void render() override;
    void process_input() override;
private:
    // Window / initialize Settings
   void draw_grid();
};
