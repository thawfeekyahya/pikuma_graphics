#include "example5.h"

#include <array>

#include "pikuma/draw.h"
#include "pikuma/projection.h"

namespace pikuma::examples {

void Example5::on_setup() {
    m_mesh = load_cube_mesh();
    m_mesh.rotation = {0.01f, 0.01f, 0.01f};
}

void Example5::update() {
    m_mesh.rotation.x += 0.01f;
    m_mesh.rotation.y += 0.01f;
    m_mesh.rotation.z += 0.01f;

    m_triangles_to_render.clear();

    for (const Face& face : m_mesh.faces) {
        const std::array<Vector3d, 3> face_vertices = {
            m_mesh.vertices[face.a - 1],
            m_mesh.vertices[face.b - 1],
            m_mesh.vertices[face.c - 1],
        };

        Triangle projected_triangle;

        for (std::size_t j = 0; j < 3; ++j) {
            Vector3d transformed_vertex = face_vertices[j];
            transformed_vertex = transformed_vertex.rotate_x(m_mesh.rotation.x);
            transformed_vertex = transformed_vertex.rotate_y(m_mesh.rotation.y);
            transformed_vertex = transformed_vertex.rotate_z(m_mesh.rotation.z);

            // Move the vertex away from the camera
            transformed_vertex.z -= m_camera_position.z;

            Vector2d projected_point = project(transformed_vertex, m_fov_factor);

            // Move to the middle of the screen
            projected_point.x += static_cast<float>(window_width()) / 2.0f;
            projected_point.y += static_cast<float>(window_height()) / 2.0f;

            projected_triangle.points[j] = projected_point;
        }

        m_triangles_to_render.push_back(projected_triangle);
    }
}

void Example5::render(ColorBuffer& buffer) {
    for (const Triangle& triangle : m_triangles_to_render) {
        draw_triangle(buffer, triangle, kYellow);
    }
}

}  // namespace pikuma::examples
