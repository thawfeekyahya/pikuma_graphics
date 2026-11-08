#include "example4.h"

#include "pikuma/draw.h"
#include "pikuma/projection.h"

namespace pikuma::examples {

void Example4::update() {
    m_cube_rotation.x += 0.01f;
    m_cube_rotation.y += 0.01f;
    m_cube_rotation.z += 0.01f;

    for (std::size_t i = 0; i < kCubeFaces.size(); ++i) {
        const Face& face = kCubeFaces[i];

        const std::array<Vector3d, 3> face_vertices = {
            kCubeVertices[face.a - 1],
            kCubeVertices[face.b - 1],
            kCubeVertices[face.c - 1],
        };

        Triangle projected_triangle;

        for (std::size_t j = 0; j < 3; ++j) {
            Vector3d transformed_vertex = face_vertices[j];
            transformed_vertex = transformed_vertex.rotate_x(m_cube_rotation.x);
            transformed_vertex = transformed_vertex.rotate_y(m_cube_rotation.y);
            transformed_vertex = transformed_vertex.rotate_z(m_cube_rotation.z);

            // Move the vertex away from the camera
            transformed_vertex.z -= m_camera_position.z;

            Vector2d projected_point = project(transformed_vertex, m_fov_factor);

            // Move to the middle of the screen
            projected_point.x += static_cast<float>(window_width()) / 2.0f;
            projected_point.y += static_cast<float>(window_height()) / 2.0f;

            projected_triangle.points[j] = projected_point;
        }

        m_triangles_to_render[i] = projected_triangle;
    }
}

void Example4::render(ColorBuffer& buffer) {
    for (const Triangle& triangle : m_triangles_to_render) {
        draw_triangle(buffer, triangle, kYellow);
    }
}

}  // namespace pikuma::examples
