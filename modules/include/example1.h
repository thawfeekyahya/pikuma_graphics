#pragma once

#include "example.h"

class Example1 : public Example {
public:
    Example1();
    void initialize() override;
    void update() override;
    void render() override;
    void process_input() override;
private:
    void draw_grid();
};
