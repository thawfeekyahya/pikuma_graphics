#pragma once

#include <vector>

#include "pikuma/example.h"
#include "pikuma/mesh.h"
#include "pikuma/triangle.h"
#include "pikuma/vector.h"

namespace pikuma::examples {

// Same as Example4, but the cube is stored in a Mesh (vertices, faces and rotation together).
class Example5 final : public Example {
public:
    Example5() = default;

    [[nodiscard]] std::string_view title() const override {
        return "Example5 - Cube stored in a Mesh";
    }
    void update() override;
    void render(ColorBuffer& buffer) override;

protected:
    void on_setup() override;

private:
    Mesh m_mesh;
    std::vector<Triangle> m_triangles_to_render;

    Vector3d m_camera_position{0.0f, 0.0f, -5.0f};
    float m_fov_factor = 640.0f;
};

}  // namespace pikuma::examples
