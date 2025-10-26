#include "mesh.h"


Mesh::Mesh() {

   mesh_vertices = {
          {-1, -1, -1},
          {-1,  1, -1},
          {1,   1, -1},
          {1,  -1, -1},
          {1,   1,  1},
          {1,  -1,  1},
          {-1,  1,  1},
          {-1, -1,  1}
   };
   
   mesh_faces = {
           {1, 2, 3},
           {1, 3, 4},
   
           {4, 3, 5},
           {4, 5, 6},
           
           {6, 5, 7},
           {6, 7, 8},
   
           {8, 7, 2},
           {8, 2, 1},
   
           {2, 7, 5},
           {2, 5, 3},
   
           {6, 8, 1},
           {6, 1, 4}
   };

}

const std::vector<pikuma::utility::Vector3d>& Mesh::getVertices() const{
    return mesh_vertices;
}

const std::vector<Face>& Mesh::getMeshFaces() const {
   return mesh_faces;
}


Mesh::Mesh(const Mesh& other) {
    mesh_faces = other.getMeshFaces();
    mesh_vertices = other.getVertices(); 
}

Mesh&  Mesh::operator=(const Mesh& other) {
    if (this == &other) return *this;

    mesh_faces = other.getMeshFaces();
    mesh_vertices = other.getVertices(); 

    return *this;
}
