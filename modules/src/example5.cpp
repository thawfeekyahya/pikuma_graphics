#include <array>
#include "example5.h"
#include <iostream>
#include "util.h"
#include <cmath>

using namespace std;
using namespace pikuma::utility;

void Example5::initialize() {
}


Example5::Example5() {
   triangles_to_render.resize(CUBE_FACES);
   loadCubeMesData();
   std::cout<<"Example5 - Re-factor example 4"<<std::endl;
}


void Example5::draw_line(int x0,int y0,int x1,int y1,uint32_t color) {
    int delta_x = x1 - x0;
    int delta_y = y1 - y0;

    int longest_side_length = std::abs(delta_x) > std::abs(delta_y) ? std::abs(delta_x) : std::abs(delta_y);

    float x_incr = delta_x / static_cast<float>(longest_side_length);
    float y_incr = delta_y / static_cast<float>(longest_side_length);

    float curr_x = x0;
    float curr_y = y0;

    for(int i=0; i<= longest_side_length; i++) {
        draw_pixel(std::round(curr_x),std::round(curr_y),color);
        curr_x += x_incr;
        curr_y += y_incr;
    }

}

void Example5::update() {

    cube_rotation.set_y(cube_rotation.get_y() + 0.01);
    cube_rotation.set_x(cube_rotation.get_x() + 0.01);
    cube_rotation.set_z(cube_rotation.get_z() + 0.01);

    int len = cube_mesh.faces.size();
    for(int i=0;i<len; i++) {

        Face cube_face = cube_mesh.faces[i];

        array<Vector3d,3> face_vertices;

        face_vertices[0] = cube_mesh.vertices[cube_face.a-1];
        face_vertices[1] = cube_mesh.vertices[cube_face.b-1];
        face_vertices[2] = cube_mesh.vertices[cube_face.c-1];

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

void Example5::draw_triangle(int x0,int y0,int x1,int y1,int x2, int y2,uint32_t color) {
    draw_line(x0,y0,x1,y1,color);
    draw_line(x1,y1,x2,y2,color);
    draw_line(x2,y2,x0,y0,color);
}


void Example5::render() {
    setup_render();

    uint32_t color = 0xFFFFFF00;

    for (int i=0; i< triangles_to_render.size(); i++) {

       Triangle triangle = triangles_to_render[i];

        draw_triangle(triangle.points[0].get_x(),triangle.points[0].get_y(),
                      triangle.points[1].get_x(),triangle.points[1].get_y(),
                      triangle.points[2].get_x(),triangle.points[2].get_y(),
                      color);
    }

    clear_render();
}

void Example5::loadCubeMesData() {

   cube_mesh.vertices.clear();
   cube_mesh.faces.clear();

    for(int i=0; i< CUBE_VERTICES; i++) {
        Vector3d cube_vertex = cube_vertices[i];
        cube_mesh.vertices.push_back(cube_vertex);
    }

    for(int i=0; i< CUBE_FACES; i++) {
        Face cube_face = cube_faces[i];
        cube_mesh.faces.push_back(cube_face);
    }
}


void Example5::process_input() {
}
