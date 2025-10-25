#include "util.h"
#include <cmath>

using namespace pikuma::utility;

Vector2d::Vector2d():x(0.0),y(0.0) {
}

Vector2d::Vector2d(float p_x,float p_y) {
    x = p_x;
    y = p_y;
}


Vector3d Vector3d::rotate_x(float angle) {

    return Vector3d(
        x,
        y * std::cos(angle) - z * std::sin(angle),
        y * std::sin(angle) + z * std::cos(angle) 
    );

}

Vector3d Vector3d::rotate_y(float angle) {
    return Vector3d(
        x * std::cos(angle) - z * std::sin(angle),
        y,
        x * std::sin(angle) + z * std::cos(angle)
    );

}

Vector3d Vector3d::rotate_z(float angle) {

    return Vector3d(
        x * std::cos(angle) - y * std::sin(angle),
        x * std::sin(angle) + y * std::cos(angle),
        z 
    );

}

Vector3d::Vector3d(): x(0.0),y(0.0),z(0.0) {
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
       z = other.z;
    }
}

Vector3d& Vector3d::operator=(const Vector3d& other) {
    if (this != &other) {
       x = other.x;
       y = other.y;
       z = other.z;
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


