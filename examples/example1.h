#pragma once

#include "pikuma/example.h"

namespace pikuma::examples {

// Draw a grid straight into the color buffer.
class Example1 final : public Example {
public:
    Example1() = default;

    [[nodiscard]] std::string_view title() const override { return "Example1 - Simple grid rendering"; }
    void render(ColorBuffer& buffer) override;
};

}  // namespace pikuma::examples
