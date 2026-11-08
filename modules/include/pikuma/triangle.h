#pragma once

#include <array>

#include "pikuma/vector.h"

namespace pikuma {

// A triangle after projection, in screen coordinates.
struct Triangle {
    std::array<Vector2d, 3> points;
};

}  // namespace pikuma
