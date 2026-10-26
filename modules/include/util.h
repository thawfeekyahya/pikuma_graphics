#pragma once
#include <array>

#include <cstdint>
#include <vector>


namespace pikuma::utility {
    
////////////////////////////////////////////////////////////////////////////////////////////////////
// Face 
////////////////////////////////////////////////////////////////////////////////////////////////////

   class Face {
      public:
      int a = 0;
      int b = 0;
      int c = 0;
   };

////////////////////////////////////////////////////////////////////////////////////////////////////
// Vector 2d
////////////////////////////////////////////////////////////////////////////////////////////////////

   class Vector2d {
       public:
          Vector2d() = default;
          Vector2d(float p_x, float p_y) : x(p_x), y(p_y) {}

          void set_x(float p_x) { x = p_x; }
          void set_y(float p_y) { y = p_y; }

          float get_x() const { return x; };
          float get_y() const { return y; };

          float get_length() const;

          Vector2d operator+(const Vector2d& other) const;
          Vector2d operator-(const Vector2d& other) const;

          Vector2d operator*(float scalar) const;
          Vector2d operator/(float scalar) const;

          float dot(const Vector2d& other) const;

          void normalize();

       private:
          float x=0.0;
          float y=0.0;
   };

////////////////////////////////////////////////////////////////////////////////////////////////////
// Vector 3d
////////////////////////////////////////////////////////////////////////////////////////////////////

   class Vector3d {
       public:
          Vector3d() = default;
          Vector3d(float p_x, float p_y, float p_z) : x(p_x), y(p_y), z(p_z) {}

          Vector3d rotate_x(float angle) const;
          Vector3d rotate_y(float angle) const;
          Vector3d rotate_z(float angle) const;

          float get_length() const;

          void set_x(float p_x) { x = p_x; }
          void set_y(float p_y) { y = p_y; }
          void set_z(float p_z) { z = p_z; }

          float get_x() const { return x; };
          float get_y() const { return y; };
          float get_z() const { return z; };
          
          Vector3d operator+(const Vector3d& other) const;
          Vector3d operator-(const Vector3d& other) const;

          Vector3d operator*(float scalar) const;
          Vector3d operator/(float scalar) const;

          Vector3d operator*(const Vector3d& other) const;
          
          float dot(const Vector3d& other) const;

          void normalize();

       private:
           float x=0.0;
           float y=0.0;
           float z=0.0;
   };
   
////////////////////////////////////////////////////////////////////////////////////////////////////
// Camera 
////////////////////////////////////////////////////////////////////////////////////////////////////

   class Camera {
      public:
         Camera() = default;
         Camera(const Vector3d& p_position, const Vector3d& p_rotation, float p_fov)
             : position(p_position), rotation(p_rotation), fov(p_fov) {}

         Vector3d position;
         Vector3d rotation;
         float fov = 0.0f; // Field of view

   };

////////////////////////////////////////////////////////////////////////////////////////////////////
// Triangle 
////////////////////////////////////////////////////////////////////////////////////////////////////

   class Triangle {
      public:
          Triangle() = default;
          std::array<Vector2d,3> points;
          void fill(uint32_t color);
          void fill_flat_bottom_triangle(Vector2d a,Vector2d b,int Mx,int My,uint32_t color);
   };

////////////////////////////////////////////////////////////////////////////////////////////////////
// Mesh 
////////////////////////////////////////////////////////////////////////////////////////////////////

   class Mesh {
      public:
        Mesh() = default;

        std::vector<Vector3d> vertices;
        std::vector<Face> faces;

        Vector3d rotation;
   };
}
