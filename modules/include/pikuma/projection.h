#pragma once

#include "pikuma/vector.h"

namespace pikuma {

// Perspective projection: divide x and y by depth (z), then scale by fov_factor.
[[nodiscard]] constexpr Vector2d project(const Vector3d& point, float fov_factor) {
    return {
        (fov_factor * point.x) / point.z,
        (fov_factor * point.y) / point.z,
    };
}

// Orthographic projection: drop z and scale. Kept for comparison with project().
[[nodiscard]] constexpr Vector2d project_orthographic(const Vector3d& point, float fov_factor) {
    return {point.x * fov_factor, point.y * fov_factor};
}

}  // namespace pikuma
