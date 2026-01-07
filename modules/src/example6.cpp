#include <array>
#include "example6.h"
#include <iostream>
#include "util.h"
#include <cmath>
#include <string>
#include <sstream>
#include <fstream>


using namespace std;
using namespace pikuma::utility;

void Example6::initialize() {
}


Example6::Example6() {
   //load_obj_data("./assets/cube.obj");
   triangles_to_render.resize(1000); // NOTE: Harcoded // assuming vertices count is under 1000
   load_obj_data("./assets/cube.obj");
   std::cout<<"Example6 - Re-factor example 4"<<std::endl;
   fov_factor= 400;
}


void Example6::draw_line(int x0,int y0,int x1,int y1,uint32_t color) {
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

void Example6::update() {

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

void Example6::draw_triangle(int x0,int y0,int x1,int y1,int x2, int y2,uint32_t color) {
    draw_line(x0,y0,x1,y1,color);
    draw_line(x1,y1,x2,y2,color);
    draw_line(x2,y2,x0,y0,color);
}


void Example6::render() {
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

void Example6::load_obj_data(const string& filename) {
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

void Example6::process_input() {
}
