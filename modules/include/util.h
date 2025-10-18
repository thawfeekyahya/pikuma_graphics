#pragma once

namespace pikuma::utility {

   class Vector2d {
       public:
          Vector2d();
          Vector2d(float p_x,float p_y);
       private:
          float x;
          float y;
          float z;
   };

   class Vector3d {
       public:
          Vector3d();
          Vector3d(float p_x,float p_y,float p_z);
          Vector3d(const Vector3d& other);
          Vector3d& operator=(const Vector3d& other);
          
       private:
           float x;
           float y;
           float z;
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
