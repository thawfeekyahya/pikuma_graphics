#include "pikuma/vector.h"

#include <cmath>

namespace pikuma {

////////////////////////////////////////////////////////////////////////////////
// Vector2d
////////////////////////////////////////////////////////////////////////////////

float Vector2d::length() const {
    return std::sqrt((x * x) + (y * y));
}

void Vector2d::normalize() {
    const float len = length();
    if (len == 0.0f) {
        return;
    }
    *this /= len;
}

////////////////////////////////////////////////////////////////////////////////
// Vector3d
////////////////////////////////////////////////////////////////////////////////

float Vector3d::length() const {
    return std::sqrt((x * x) + (y * y) + (z * z));
}

void Vector3d::normalize() {
    const float len = length();
    if (len == 0.0f) {
        return;
    }
    *this /= len;
}

Vector3d Vector3d::rotate_x(float angle) const {
    const float c = std::cos(angle);
    const float s = std::sin(angle);
    return {
        x,
        (y * c) - (z * s),
        (y * s) + (z * c),
    };
}

Vector3d Vector3d::rotate_y(float angle) const {
    const float c = std::cos(angle);
    const float s = std::sin(angle);
    return {
        (x * c) - (z * s),
        y,
        (x * s) + (z * c),
    };
}

Vector3d Vector3d::rotate_z(float angle) const {
    const float c = std::cos(angle);
    const float s = std::sin(angle);
    return {
        (x * c) - (y * s),
        (x * s) + (y * c),
        z,
    };
}

}  // namespace pikuma
