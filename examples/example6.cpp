#include "example6.h"

#include <array>
#include <iostream>
#include <utility>

#include "pikuma/draw.h"
#include "pikuma/projection.h"

namespace pikuma::examples {

namespace {
constexpr const char* kMeshPath = "./assets/Car.obj";
}

void Example6::on_setup() {
    if (auto mesh = load_obj_file(kMeshPath)) {
        m_mesh = std::move(*mesh);
    } else {
        std::cerr << "Failed to open " << kMeshPath << '\n';
    }
    m_mesh.rotation = {0.01f, 0.01f, 0.01f};
}

void Example6::update() {
    m_mesh.rotation.y += 0.01f;

    m_triangles_to_render.clear();

    for (const Face& face : m_mesh.faces) {
        const std::array<Vector3d, 3> face_vertices = {
            m_mesh.vertices[face.a - 1],
            m_mesh.vertices[face.b - 1],
            m_mesh.vertices[face.c - 1],
        };

        // Transform each vertex of the face
        std::array<Vector3d, 3> transformed_vertices;
        for (std::size_t j = 0; j < 3; ++j) {
            Vector3d transformed_vertex = face_vertices[j];
            transformed_vertex = transformed_vertex.rotate_x(m_mesh.rotation.x);
            transformed_vertex = transformed_vertex.rotate_y(m_mesh.rotation.y);
            transformed_vertex = transformed_vertex.rotate_z(m_mesh.rotation.z);

            // Move the vertex away from the camera
            transformed_vertex.z += kDepthOffset;

            transformed_vertices[j] = transformed_vertex;
        }

        // Back-face culling
        const Vector3d& vector_a = transformed_vertices[0];
        const Vector3d& vector_b = transformed_vertices[1];
        const Vector3d& vector_c = transformed_vertices[2];

        // Face normal
        Vector3d normal = cross(vector_b - vector_a, vector_c - vector_a);
        normal.normalize();

        // Vector from a point on the face to the camera
        const Vector3d camera_ray = m_camera_position - vector_a;

        // Skip the face if its normal points away from the camera
        if (dot(normal, camera_ray) < 0.0f) {
            continue;
        }

        // Project the vertices that passed the culling test
        Triangle projected_triangle;
        for (std::size_t j = 0; j < 3; ++j) {
            Vector2d projected_point = project(transformed_vertices[j], m_fov_factor);

            // Move to the middle of the screen
            projected_point.x += static_cast<float>(window_width()) / 2.0f;
            projected_point.y += static_cast<float>(window_height()) / 2.0f;

            projected_triangle.points[j] = projected_point;
        }

        m_triangles_to_render.push_back(projected_triangle);
    }
}

void Example6::render(ColorBuffer& buffer) {
    for (const Triangle& triangle : m_triangles_to_render) {
        draw_triangle(buffer, triangle, kYellow);
    }
}

}  // namespace pikuma::examples
