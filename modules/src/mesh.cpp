#include "pikuma/mesh.h"

#include <fstream>
#include <sstream>

namespace pikuma {

namespace {

// Reads the vertex index from an .obj face token.
// Tokens look like "v", "v/vt", "v//vn" or "v/vt/vn". Only "v" is used for now.
std::optional<int> parse_vertex_index(const std::string& token) {
    try {
        return std::stoi(token.substr(0, token.find('/')));
    } catch (...) {
        return std::nullopt;
    }
}

}  // namespace

Mesh load_cube_mesh() {
    Mesh mesh;
    mesh.vertices.assign(kCubeVertices.begin(), kCubeVertices.end());
    mesh.faces.assign(kCubeFaces.begin(), kCubeFaces.end());
    return mesh;
}

std::optional<Mesh> load_obj_file(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        return std::nullopt;
    }

    Mesh mesh;
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (type == "v") {
            Vector3d vertex;
            iss >> vertex.x >> vertex.y >> vertex.z;
            mesh.vertices.push_back(vertex);
        } else if (type == "f") {
            std::vector<int> indices;
            std::string token;
            while (iss >> token) {
                if (auto index = parse_vertex_index(token)) {
                    indices.push_back(*index);
                }
            }
            // Only triangles are supported, so extra vertices are ignored.
            if (indices.size() >= 3) {
                mesh.faces.push_back({indices[0], indices[1], indices[2]});
            }
        }
    }

    return mesh;
}

}  // namespace pikuma
