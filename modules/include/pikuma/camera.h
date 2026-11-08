#pragma once

#include "pikuma/vector.h"

namespace pikuma {

struct Camera {
    Vector3d position;
    Vector3d rotation;
    float fov = 0.0f;  // field of view
};

}  // namespace pikuma
