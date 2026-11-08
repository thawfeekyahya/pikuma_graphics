#pragma once

#include <array>

#include "pikuma/example.h"
#include "pikuma/vector.h"

namespace pikuma::examples {

// A 9x9x9 cube of points, rotated on x, y and z, with perspective projection.
class Example3 final : public Example {
public:
    Example3() = default;

    [[nodiscard]] std::string_view title() const override {
        return "Example3 - Plot 9x9x9 points of a cube and rotate on x, y and z";
    }
    void update() override;
    void render(ColorBuffer& buffer) override;

protected:
    void on_setup() override;

private:
    static constexpr int kPointCount = 9 * 9 * 9;

    std::array<Vector3d, kPointCount> m_cube_points{};
    std::array<Vector2d, kPointCount> m_projected_points{};

    Vector3d m_cube_rotation{0.01f, 0.01f, 0.01f};
    Vector3d m_camera_position{0.0f, 0.0f, -5.0f};
    float m_fov_factor = 640.0f;
};

}  // namespace pikuma::examples
