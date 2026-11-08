#pragma once

#include <vector>

#include "pikuma/example.h"
#include "pikuma/mesh.h"
#include "pikuma/triangle.h"
#include "pikuma/vector.h"

namespace pikuma::examples {

// Load a mesh from an .obj file and skip faces pointing away from the camera (back-face culling).
class Example6 final : public Example {
public:
    Example6() = default;

    [[nodiscard]] std::string_view title() const override {
        return "Example6 - Load .obj file with back-face culling";
    }
    void update() override;
    void render(ColorBuffer& buffer) override;

protected:
    void on_setup() override;

private:
    Mesh m_mesh;
    std::vector<Triangle> m_triangles_to_render;

    // The camera is at the origin. Each vertex is moved forward by kDepthOffset instead,
    // so the camera ray used for culling is simply (camera - vertex).
    static constexpr float kDepthOffset = 8.0f;
    Vector3d m_camera_position{0.0f, 0.0f, 0.0f};
    float m_fov_factor = 400.0f;
};

}  // namespace pikuma::examples
