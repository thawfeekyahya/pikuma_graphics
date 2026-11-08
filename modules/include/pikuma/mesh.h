#pragma once

#include <array>
#include <optional>
#include <string>
#include <vector>

#include "pikuma/vector.h"

namespace pikuma {

// One triangle of a mesh, stored as three vertex indices.
// Indices are 1-based, the same as in .obj files and the course code,
// so look a vertex up with `mesh.vertices[face.a - 1]`.
struct Face {
    int a = 0;
    int b = 0;
    int c = 0;
};

struct Mesh {
    std::vector<Vector3d> vertices;
    std::vector<Face> faces;
    Vector3d rotation;
};

// Hard-coded unit cube (8 vertices, 12 triangles), the same as `cube_vertices`/`cube_faces` in mesh.c.
inline constexpr std::size_t kCubeVertexCount = 8;
inline constexpr std::size_t kCubeFaceCount = 6 * 2;

inline constexpr std::array<Vector3d, kCubeVertexCount> kCubeVertices = {{
    {-1, -1, -1},  // 1
    {-1, 1, -1},   // 2
    {1, 1, -1},    // 3
    {1, -1, -1},   // 4
    {1, 1, 1},     // 5
    {1, -1, 1},    // 6
    {-1, 1, 1},    // 7
    {-1, -1, 1},   // 8
}};

inline constexpr std::array<Face, kCubeFaceCount> kCubeFaces = {{
    // front
    {1, 2, 3},
    {1, 3, 4},
    // right
    {4, 3, 5},
    {4, 5, 6},
    // back
    {6, 5, 7},
    {6, 7, 8},
    // left
    {8, 7, 2},
    {8, 2, 1},
    // top
    {2, 7, 5},
    {2, 5, 3},
    // bottom
    {6, 8, 1},
    {6, 1, 4},
}};

// Builds a Mesh from kCubeVertices / kCubeFaces.
[[nodiscard]] Mesh load_cube_mesh();

// Reads the vertices ("v") and triangle faces ("f") of an .obj file.
// Returns std::nullopt if the file cannot be opened.
[[nodiscard]] std::optional<Mesh> load_obj_file(const std::string& path);

}  // namespace pikuma
