#include "util.h"

using namespace pikuma::utility;

Vector2d::Vector2d():x(0),y(0) {
}

Vector2d::Vector2d(float p_x,float p_y) {
    x = p_x;
    y = p_y;
}

Vector3d::Vector3d(): x(0),y(0),z(0) {
}

Vector3d::Vector3d(float p_x,float p_y,float p_z) {

    x = p_x;
    y = p_y;
    z = p_z;
}

Vector3d::Vector3d(const Vector3d& other) {
    if (this != &other) {
       x = other.x;
       y = other.y;
       z = other.y;
    }
}

Vector3d& Vector3d::operator=(const Vector3d& other) {
    if (this != &other) {
       x = other.x;
       y = other.y;
       z = other.y;
    }
    return *this;
}

Camera::Camera() {

}

Camera::Camera(Vector3d& p_position,Vector3d& p_rotation, float p_fov):
   position(p_position),
   rotation(p_rotation),
   fov(p_fov)
{
}


