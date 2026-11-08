#pragma once

#include "pikuma/example.h"

namespace pikuma::examples {

// Draw a rectangle with draw_pixel.
class Example2 final : public Example {
public:
    Example2() = default;

    [[nodiscard]] std::string_view title() const override {
        return "Example2 - Draw rectangle using draw_pixel";
    }
    void render(ColorBuffer& buffer) override;
};

}  // namespace pikuma::examples
