#include "example3.h"

#include "pikuma/draw.h"
#include "pikuma/projection.h"

namespace pikuma::examples {

void Example3::on_setup() {
    // Points from -1 to 1 in steps of 0.25 on each axis (9 per axis).
    // Integer loop counters avoid float rounding errors adding up.
    int point_count = 0;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            for (int k = 0; k < 9; ++k) {
                m_cube_points[point_count++] = {
                    -1.0f + (0.25f * static_cast<float>(i)),
                    -1.0f + (0.25f * static_cast<float>(j)),
                    -1.0f + (0.25f * static_cast<float>(k)),
                };
            }
        }
    }
}

void Example3::update() {
    m_cube_rotation.x += 0.01f;
    m_cube_rotation.y += 0.01f;
    m_cube_rotation.z += 0.01f;

    for (int i = 0; i < kPointCount; ++i) {
        Vector3d point = m_cube_points[i];

        Vector3d transformed_point = point.rotate_x(m_cube_rotation.x);
        transformed_point = transformed_point.rotate_y(m_cube_rotation.y);
        transformed_point = transformed_point.rotate_z(m_cube_rotation.z);

        // Move the points away from the camera (after rotating)
        transformed_point.z -= m_camera_position.z;

        m_projected_points[i] = project(transformed_point, m_fov_factor);
    }
}

void Example3::render(ColorBuffer& buffer) {
    const float half_width = static_cast<float>(window_width()) / 2.0f;
    const float half_height = static_cast<float>(window_height()) / 2.0f;

    for (const Vector2d& point : m_projected_points) {
        draw_rect(buffer, static_cast<int>(point.x + half_width), static_cast<int>(point.y + half_height), 4, 4,
                  kYellow);
    }
}

}  // namespace pikuma::examples
