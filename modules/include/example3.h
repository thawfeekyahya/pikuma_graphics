#pragma once
#include "example.h"

class Example3 : public Example {
public:
    Example3() = default;
    void initialize() override;
    void update() override;
    void render() override;
    void process_input() override;
};
