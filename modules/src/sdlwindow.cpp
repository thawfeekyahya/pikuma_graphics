#include "sdlwindow.h"

#include <iostream>
#include <SDL2/SDL.h>
#include "mesh.h"
#include <vector>
#include "util.h"

using namespace std;
using namespace pikuma::utility;



void SdlWindow::setup() {
    uint total_len = screen_width * screen_height;
    color_buffer = new uint32_t[total_len];
}

void SdlWindow::populate_dot_array_cube() {

    int point_count = 0;
    
    for (float x=-1; x <= 1; x+= 0.25) {
        for (float y=-1; y <=1; y+=0.25) {
            for (float z=-1; z<=1; z+=0.25) {
                Vector3d new_point(x,y,z);
                cube_points[point_count++] = new_point;
            }
        }
    }
}

void SdlWindow::populate_cube_vertices() {
     
}

Vector2d SdlWindow::project(Vector3d point) {
    float fov_factor = 640;
    Vector2d projected_point(
                             fov_factor * point.get_x() / point.get_z(),
                             fov_factor * point.get_y() / point.get_z()
                             );
    return projected_point;
}

SdlWindow::~SdlWindow() {
    destroy_window();
}

void SdlWindow::draw_pixel(int x,int y, uint32_t color) {
    if ((x >=0 && x < screen_width) && (y >= 0 && y < screen_height)) {
        color_buffer[ screen_width * y + x ] = color;
    }
}


void SdlWindow::destroy_window() {
    delete color_buffer;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void SdlWindow::initialize() {
    
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        cout<<"Error"<<endl;
    } else {
        cout<<"Success"<<endl;
    }


    //Query window max size
    SDL_DisplayMode display_mode;
    SDL_GetCurrentDisplayMode(0,&display_mode);

    screen_width = display_mode.w;
    screen_height = display_mode.h;

    //Create SDL window
    window = SDL_CreateWindow(NULL,SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              screen_width,screen_height,      
                              SDL_WINDOW_BORDERLESS);

    if (window == nullptr) {
        cout<<"Error creating SDL window"<<endl;
        m_isRunning = false;
    }

    //Create SDL Renderer
    renderer = SDL_CreateRenderer(window,-1,0);

    if (renderer == nullptr) {
        cout<<"Error creating SDL Renderer"<<endl;
        m_isRunning = false;
    }

    //Initialize the texture
    color_buffer_texture = SDL_CreateTexture(renderer,
                                             SDL_PIXELFORMAT_ARGB8888,
                                             SDL_TEXTUREACCESS_STREAMING,
                                             screen_width,
                                             screen_height);

    SDL_SetWindowFullscreen(window,SDL_WINDOW_FULLSCREEN);

    m_isRunning = true;
}

void SdlWindow::render_color_buffer () {
    SDL_UpdateTexture(
        color_buffer_texture,
        nullptr,
        color_buffer,
        screen_width * sizeof(uint32_t)
    );

    SDL_RenderCopy(renderer,color_buffer_texture,nullptr,nullptr);
}


bool SdlWindow::isRunning() const {
    return m_isRunning;
}


Vector3d camera_pos(0.0,0.0,-5.0);


void SdlWindow::update() {
 
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks()- previous_frame_time);   
    previous_frame_time = SDL_GetTicks();

    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
        SDL_Delay(time_to_wait);
    }

    cube_rotation.set_y(cube_rotation.get_y() + 0.01);
    cube_rotation.set_x(cube_rotation.get_x() + 0.01);
    cube_rotation.set_z(cube_rotation.get_z() + 0.01);




    for(int i=0; i<N_MESH_FACES; i++) {
        Mesh mesh;
        Face face = mesh.getMeshFaces()[i]; 

        vector<Vector3d> face_vertices{3};

        face_vertices[0] = mesh.getVertices()[face.get_a()-1];
        face_vertices[1] = mesh.getVertices()[face.get_b()-1];
        face_vertices[2] = mesh.getVertices()[face.get_c()-1];


        Triangle projected_triangle;

        for (int j=0; j<3; j++) {
            Vector3d transformed_vertex = face_vertices[j];

            transformed_vertex = transformed_vertex.rotate_x(cube_rotation.get_x());
            transformed_vertex = transformed_vertex.rotate_y(cube_rotation.get_y());
            transformed_vertex = transformed_vertex.rotate_z(cube_rotation.get_z());


           Vector2d projected_point = project(transformed_vertex);

            projected_triangle.points[j] = projected_point;
        }

        triangles_to_render[i] = projected_triangle;
     }

    /*
       for (int i=0; i< N_POINTS; i++) {
           Vector3d point = cube_points[i];

          Vector3d transformed_point = point.rotate_x(cube_rotation.get_x());
          transformed_point = transformed_point.rotate_y(cube_rotation.get_y());
          transformed_point = transformed_point.rotate_z(cube_rotation.get_z());

           transformed_point.set_z(transformed_point.get_z() - camera_pos.get_z());
           Vector2d projected_point = project(transformed_point);

           projected_points[i] = projected_point;
       }
    */
}


void SdlWindow::process_input() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            m_isRunning = false;
        break;

        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                m_isRunning = false;
            }
       break;

    }
}


void SdlWindow::draw_rectangle(uint x,uint y,uint width,uint height,uint32_t color){ 

    for (uint i=0; i < height; i++) {
        for (uint j=0; j < width; j++) {
            uint curr_x = x + j;
            uint curr_y = y + i;
            draw_pixel(curr_x,curr_y,color);
        }
    }
}

void SdlWindow::clear_color_buffer(uint32_t color) {
    for (uint y=0; y < screen_height; y++) {
        for (uint x=0; x < screen_width; x++) {
            color_buffer[(screen_width * y) + x] = color;
        }
    }
}

void SdlWindow::draw_grid() {
    int rowSize = 10;
    int colSize = 10;

    for (int y=0; y< screen_height; y++ ) {
        for (int x=0; x < screen_width; x++) {
             if ( x % rowSize == 0 || y % colSize == 0) {
                color_buffer[(screen_width * y) +x ] = 0xFFFF0000;
            }
        }
    }
}

void SdlWindow::render() {
    // --- Phase 1
    //SDL_SetRenderDrawColor(renderer,255,0,0,255);
    //SDL_RenderClear(renderer);

    //draw_grid();
    //draw_rectangle(40,70,30,30,0xFF0000FF);
    //

    // --- Phase 2
    //for (int i =0; i< N_POINTS; i++) {
    //    Vector2d projected_point = projected_points[i];
    //    draw_rectangle(
    //      projected_point.get_x() + (screen_width *  0.5), 
    //      projected_point.get_y() + (screen_height * 0.5),
    //      4,4,
    //      0xFFFFFF00
    //    );
    //}

    // --- Phase 3

     
    render_color_buffer();
    clear_color_buffer(0xFF000000);

    SDL_RenderPresent(renderer);
}
