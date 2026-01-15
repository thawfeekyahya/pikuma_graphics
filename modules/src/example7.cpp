#include <array>
#include "example7.h"
#include <iostream>
#include "util.h"
#include <cmath>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>


using namespace std;
using namespace pikuma::utility;

void Example7::initialize() {
}


Example7::Example7() {
   //load_obj_data("./assets/cube.obj");
   triangles_to_render.resize(1000); // NOTE: Harcoded // assuming vertices count is under 1000
   load_obj_data("./assets/cube.obj");
   std::cout<<"Example7 - Re-factor example 4"<<std::endl;
   fov_factor= 400;
}


void Example7::draw_line(int x0,int y0,int x1,int y1,uint32_t color) {
    int delta_x = x1 - x0;
    int delta_y = y1 - y0;

    int longest_side_length = abs(delta_x) > abs(delta_y) ? abs(delta_x) : abs(delta_y);

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

void Example7::update() {

    cube_rotation.set_y(cube_rotation.get_y() + 0.01);
    cube_rotation.set_x(cube_rotation.get_x() + 0.01);
    cube_rotation.set_z(cube_rotation.get_z() + 0.01);

    triangles_to_render.clear();

    int len = cube_mesh.faces.size();
    for(int i=0;i<len; i++) {

        Face cube_face = cube_mesh.faces[i];

        array<Vector3d,3> face_vertices;

        face_vertices[0] = cube_mesh.vertices[cube_face.a-1];
        face_vertices[1] = cube_mesh.vertices[cube_face.b-1];
        face_vertices[2] = cube_mesh.vertices[cube_face.c-1];

        Triangle projected_triangle;

        vector<Vector3d> transformed_vertices(3);

        //For loop for transformation of each vertex in the faces
        for (int j=0; j<3; j++) {
            Vector3d transformed_vertex = face_vertices[j];

            transformed_vertex = transformed_vertex.rotate_x(cube_rotation.get_x());
            transformed_vertex = transformed_vertex.rotate_y(cube_rotation.get_y());
            transformed_vertex = transformed_vertex.rotate_z(cube_rotation.get_z());

            //Translate the vertex away from Camera
            // Hardcode the camera position for z , since camera's dot product needs to be calcuated for culling
            transformed_vertex.set_z(transformed_vertex.get_z() + 5);

            transformed_vertices[j] = transformed_vertex;
        } 


        //Check Culling
        
        Vector3d vec_a = transformed_vertices[0];
        Vector3d vec_b = transformed_vertices[1];
        Vector3d vec_c = transformed_vertices[2];

        Vector3d vec_ab = vec_b - vec_a;
        Vector3d vec_ac = vec_c - vec_a;

        //Find face normal
        Vector3d normal = vec_ab * vec_ac;
        normal.normalize();
        
        //Find vector of camera to the the object point
        Vector3d camera_ray = camera_pos - vec_a;

        //Find the dot product between camera and face points
        float dot_normal_camera = normal.dot(camera_ray);


        if (dot_normal_camera < 0 ) {
            continue;
        }


        //For loop for projecting after culling test
        for(int j=0; j<3; j++) {

            //Project current vertex
            Vector2d projected_point = project(transformed_vertices[j]);

            //Scale and translate to middle of the scren
            projected_point.set_x(projected_point.get_x() + screen_width/2);
            projected_point.set_y(projected_point.get_y() + screen_height/2);

            projected_triangle.points[j] = projected_point;
        }

        triangles_to_render.push_back(projected_triangle);
    }
}

void Example7::draw_triangle(int x0,int y0,int x1,int y1,int x2, int y2,uint32_t color) {
    draw_line(x0,y0,x1,y1,color);
    draw_line(x1,y1,x2,y2,color);
    draw_line(x2,y2,x0,y0,color);
}


void Example7::render() {
    setup_render();

    uint32_t color = 0xFFFFFF00;

    for (int i=0; i< triangles_to_render.size(); i++) {

       Triangle triangle = triangles_to_render[i];

        draw_filled_triangle(triangle.points[0].get_x(),triangle.points[0].get_y(),
                      triangle.points[1].get_x(),triangle.points[1].get_y(),
                      triangle.points[2].get_x(),triangle.points[2].get_y(),
                      color);

        draw_triangle(triangle.points[0].get_x(),triangle.points[0].get_y(),
                      triangle.points[1].get_x(),triangle.points[1].get_y(),
                      triangle.points[2].get_x(),triangle.points[2].get_y(),
                      0xFF000000);
    }

    //draw_triangle(300,100,50,400,500,700,0xFF00FF0000);
    //draw_filled_triangle(300,100,50,400,500,700,0xFF00FF0000);


    clear_render();
}

void Example7::load_obj_data(const string& filename) {
    cube_mesh.vertices.clear();
    cube_mesh.faces.clear();

    ifstream file(filename);

    if (!file.is_open()) {
        cerr<<"Failed to open the file"<<endl;
        return;
    }

    string line;

    while(getline(file,line)) {
        if (line.empty() || line[0] == '#') continue;

        istringstream iss(line);
        string type;
        iss >> type;

        if( type == "v") {
            Vector3d cube_vertex; 
            float x,y,z;

            //each >> will read next string in the loop of string stream
            iss>>x>>y>>z;
            cube_vertex.set_x(x);
            cube_vertex.set_y(y);
            cube_vertex.set_z(z);

            cube_mesh.vertices.push_back(cube_vertex);


        } else if ( type == "f" ) {

            string token;
            vector<int> v_indices;
            vector<int> vt_indices;
            vector<int> vn_indices;

            Face cube_face;

            while(iss>>token) {
                int v=-1, vt=-1, vn=-1;

                //istringstream ss(token);
                size_t first_slash = token.find('/');
                size_t second_slash = token.find('/',first_slash + 1);

                try {
                    v = stoi(token.substr(0,first_slash));
                    
                    if (second_slash != string::npos && second_slash > first_slash + 1) {
                        vt = stoi(token.substr(first_slash+1,second_slash - first_slash - 1));
                    }

                    if (second_slash != string::npos) {
                        vn = stoi(token.substr(second_slash + 1));
                    }

                } catch (...) {
                    //malinformed
                }

                v_indices.push_back(v);
                vt_indices.push_back(vt);
                vn_indices.push_back(vn);
            }

            cube_face.a = v_indices[0];
            cube_face.b = v_indices[1];
            cube_face.c = v_indices[2];
            cube_mesh.faces.push_back(cube_face);
        }
    }

    file.close();
}

void Example7::process_input() {
}


void Example7::draw_filled_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
    // We need to sort the vertices by y-coordinate ascending (y0 < y1 < y2)
    if (y0 > y1) {
        swap(y0, y1);
        swap(x0, x1);
    }
    if (y1 > y2) {
        swap(y1, y2);
        swap(x1, x2);
    }
    if (y0 > y1) {
        swap(y0, y1);
        swap(x0, x1);
    }

    if (y1 == y2) {
        // Draw flat-bottom triangle
        fill_flat_bottom_triangle(x0, y0, x1, y1, x2, y2, color);
    } else if (y0 == y1) {
        // Draw flat-top triangle
        fill_flat_top_triangle(x0, y0, x1, y1, x2, y2, color);
    } else {
        // Calculate the new vertex (Mx,My) using triangle similarity
        int My = y1;
        int Mx = (((x2 - x0) * (y1 - y0)) / (y2 - y0)) + x0;

        // Draw flat-bottom triangle
        fill_flat_bottom_triangle(x0, y0, x1, y1, Mx, My, color);

        // Draw flat-top triangle
        fill_flat_top_triangle(x1, y1, Mx, My, x2, y2, color);
    }
}

void Example7::fill_flat_bottom_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
    // Find the two slopes (two triangle legs)
    float inv_slope_1 = (float)(x1 - x0) / (y1 - y0);
    float inv_slope_2 = (float)(x2 - x0) / (y2 - y0);

    // Start x_start and x_end from the top vertex (x0,y0)
    float x_start = x0;
    float x_end = x0;

    // Loop all the scanlines from top to bottom
    for (int y = y0; y <= y2; y++) {
        draw_line(x_start, y, x_end, y, color);
        x_start += inv_slope_1;
        x_end += inv_slope_2;
    }
}


void Example7::fill_flat_top_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
    // Find the two slopes (two triangle legs)
    float inv_slope_1 = (float)(x2 - x0) / (y2 - y0);
    float inv_slope_2 = (float)(x2 - x1) / (y2 - y1);

    // Start x_start and x_end from the bottom vertex (x2,y2)
    float x_start = x2;
    float x_end = x2;

    // Loop all the scanlines from bottom to top
    for (int y = y2; y >= y0; y--) {
        draw_line(x_start, y, x_end, y, color);
        x_start -= inv_slope_1;
        x_end -= inv_slope_2;
    }
}

