#include <array>
#include "example4.h"
#include <iostream>
#include "util.h"


using namespace std;
using namespace pikuma::utility;

void Example4::initialize() {
}


Example4::Example4() {
   std::cout<<"Example4 - Draw vertex and triangles"<<std::endl;
}


void Example4::update() {

    cube_rotation.set_y(cube_rotation.get_y() + 0.01);
    cube_rotation.set_x(cube_rotation.get_x() + 0.01);
    cube_rotation.set_z(cube_rotation.get_z() + 0.01);

    for(int i=0;i<MESH_FACES; i++) {
        Face mesh_face = mesh_faces[i];

        array<Vector3d,3> face_vertices;

        face_vertices[0] = mesh_vertices[mesh_face.a-1];
        face_vertices[1] = mesh_vertices[mesh_face.b-1];
        face_vertices[2] = mesh_vertices[mesh_face.c-1];

        Triangle projected_triangle;

        for (int j=0; j<3; j++) {
            Vector3d transformed_vertex = face_vertices[j];

            transformed_vertex = transformed_vertex.rotate_x(cube_rotation.get_x());
            transformed_vertex = transformed_vertex.rotate_y(cube_rotation.get_y());
            transformed_vertex = transformed_vertex.rotate_z(cube_rotation.get_z());

            //Translate the vertex away from Camera 
            transformed_vertex.set_z( transformed_vertex.get_z() - camera_pos.get_z()); 

            //Project current vertex
            Vector2d projected_point = Example3::project(transformed_vertex);

            //Scale and translate to middle of the scren
            projected_point.set_x(projected_point.get_x() + screen_width/2);
            projected_point.set_y(projected_point.get_y() + screen_height/2);

            projected_triangle.points[j] = projected_point;
        }
        

        triangles_to_render[i] = projected_triangle;

    }
}

void Example4::render() {
    setup_render();

    for (int i=0; i< MESH_FACES; i++) {
       Triangle triangle = triangles_to_render[i];
        draw_rectangle( triangle.points[0].get_x(),triangle.points[0].get_y(), 3,3,0xFFFFFF00);
        draw_rectangle( triangle.points[1].get_x(),triangle.points[1].get_y(), 3,3,0xFFFFFF00);
        draw_rectangle( triangle.points[2].get_x(),triangle.points[2].get_y(), 3,3,0xFFFFFF00);

    }

    clear_render();
}


void Example4::process_input() {
}
