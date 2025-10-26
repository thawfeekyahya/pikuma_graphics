#pragma once

#include "util.h"
#include "triangle.h"
#include <vector>

#define N_MESH_VERTICES  8
#define N_MESH_FACES  (6 * 2)
class Mesh {

public:
    Mesh();
    Mesh(const Mesh& other);
    Mesh& operator=(const Mesh& other);

    const std::vector<pikuma::utility::Vector3d>& getVertices() const;
    const std::vector<Face>& getMeshFaces() const;

private:

    std::vector<pikuma::utility::Vector3d> mesh_vertices{N_MESH_VERTICES};
    std::vector<Face> mesh_faces{N_MESH_FACES}; 
};
