#pragma once

#include <array>

#include "pikuma/example.h"
#include "pikuma/mesh.h"
#include "pikuma/triangle.h"
#include "pikuma/vector.h"

namespace pikuma::examples {

// Cube made of vertices and triangle faces, drawn as a wireframe.
class Example4 final : public Example {
public:
    Example4() = default;

    [[nodiscard]] std::string_view title() const override {
        return "Example4 - Cube vertices and triangle faces drawn as lines";
    }
    void update() override;
    void render(ColorBuffer& buffer) override;

private:
    std::array<Triangle, kCubeFaceCount> m_triangles_to_render{};

    Vector3d m_cube_rotation{0.01f, 0.01f, 0.01f};
    Vector3d m_camera_position{0.0f, 0.0f, -5.0f};
    float m_fov_factor = 640.0f;
};

}  // namespace pikuma::examples
