#pragma once

#include <iostream>

namespace pikuma::utility {

   class Vector2d {
       public:
          Vector2d();
          Vector2d(float p_x,float p_y);

          void set_x(float p_x) { x = p_x; }
          void set_y(float p_y) { y = p_y; }

          float get_x() const { return x; };
          float get_y() const { return y; };
       private:
          float x=0.0;
          float y=0.0;
   };

   class Vector3d {
       public:
          Vector3d();
          Vector3d(float p_x,float p_y,float p_z);
          Vector3d(const Vector3d& other);
          Vector3d& operator=(const Vector3d& other);

          void set_x(float p_x) { x = p_x; }
          void set_y(float p_y) { y = p_y; }
          void set_z(float p_z) { z = p_z; }

          float get_x() const { return x; };
          float get_y() const { return y; };
          float get_z() const { return z; };
          
       private:
           float x=0.0;
           float y=0.0;
           float z=0.0;
   };
   
   class Camera {
      public:
         Camera();
         Camera(Vector3d& p_position,Vector3d& p_rotation,float p_fov);
      private:
         Vector3d position;
         Vector3d rotation;
         float fov; // Field of view

   };
}
