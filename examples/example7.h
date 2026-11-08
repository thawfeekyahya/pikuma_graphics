#pragma once

#include <vector>

#include "pikuma/example.h"
#include "pikuma/mesh.h"
#include "pikuma/triangle.h"
#include "pikuma/vector.h"

namespace pikuma::examples {

// Solid triangles (flat-bottom / flat-top fill) with a wireframe drawn on top.
class Example7 final : public Example {
public:
    Example7() = default;

    [[nodiscard]] std::string_view title() const override { return "Example7 - Filled triangles"; }
    void update() override;
    void render(ColorBuffer& buffer) override;

protected:
    void on_setup() override;

private:
    Mesh m_mesh;
    std::vector<Triangle> m_triangles_to_render;

    // The camera is at the origin. Each vertex is moved forward by kDepthOffset instead,
    // so the camera ray used for culling is simply (camera - vertex).
    static constexpr float kDepthOffset = 5.0f;
    Vector3d m_camera_position{0.0f, 0.0f, 0.0f};
    float m_fov_factor = 400.0f;
};

}  // namespace pikuma::examples
