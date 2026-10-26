#include "util.h"
#include <cmath>
#include <vector>
#include <array>
#include <algorithm>


using namespace pikuma::utility;
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Vector 2d
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float Vector2d::get_length() const {
    return std::sqrt(x*x + y*y);
}

float Vector3d::get_length() const {
    return std::sqrt(x*x + y*y + z*z);
}

Vector2d Vector2d::operator+(const Vector2d& other) const {
    return {
        x + other.x ,
        y + other.y
    };
}

Vector2d Vector2d::operator-(const Vector2d& other) const {
    return {
        x - other.x ,
        y - other.y
    };
}

Vector2d Vector2d::operator*(float scalar) const {
    return {
        x * scalar,
        y * scalar
    };
}

Vector2d Vector2d::operator/(float scalar) const {
    return {
        x / scalar,
        y / scalar
    };
}


float Vector2d::dot(const Vector2d& other) const {
    return x*other.x + y*other.y;
}

void Vector2d::normalize() {
    float len = get_length();
    if (len == 0.0f) {
        return;
    }
    x /= len;
    y /= len;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Vector 3d
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Vector3d Vector3d::operator-(const Vector3d& other) const {
    return {
        x - other.x ,
        y - other.y,
        z - other.z
    };
}

Vector3d Vector3d::operator+(const Vector3d& other) const {
    return {
        x + other.x ,
        y + other.y ,
        z + other.z
    };
}

Vector3d Vector3d::rotate_x(float angle) const {

    return Vector3d(
        x,
        y * std::cos(angle) - z * std::sin(angle),
        y * std::sin(angle) + z * std::cos(angle) 
    );

}

Vector3d Vector3d::rotate_y(float angle) const {
    return Vector3d(
        x * std::cos(angle) - z * std::sin(angle),
        y,
        x * std::sin(angle) + z * std::cos(angle)
    );

}

Vector3d Vector3d::rotate_z(float angle) const {

    return Vector3d(
        x * std::cos(angle) - y * std::sin(angle),
        x * std::sin(angle) + y * std::cos(angle),
        z 
    );

}

Vector3d Vector3d::operator*(float scalar) const {
    return {
        x * scalar,
        y * scalar,
        z * scalar
    };
}


Vector3d Vector3d::operator*(const Vector3d& other) const {
    return {
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    };
}

Vector3d Vector3d::operator/(float scalar) const {
    return {
        x / scalar,
        y / scalar,
        z / scalar
    };
}

float Vector3d::dot(const Vector3d& other) const {
    return x * other.x + y * other.y + z * other.z;
}

void Vector3d::normalize() {
    float len = get_length();
    if (len == 0.0f) {
        return;
    }
    x /= len;
    y /= len;
    z /= len;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Camera
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Triangle
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Triangle::fill(uint32_t color) {
    std:array<Vector2d,3> copy = points;
    std::sort(copy.begin(),copy.end(),[](
                                const Vector2d& a,const Vector2d& b) {
                                    return a.get_y() > b.get_y();
                                });
    int My = copy[1].get_y();
    int Mx = ((copy[2].get_x()-copy[0].get_x() * copy[1].get_y() - copy[0].get_y()) / (copy[2].get_y() - copy[0].get_y())) + copy[0].get_x();
   
    fill_flat_bottom_triangle(copy[0],copy[1],Mx,My,0xFF000000);

    //fill_flat_top_triangle(copy[1],Mx,My,copy[2]);
}

void Triangle::fill_flat_bottom_triangle(Vector2d a,Vector2d b,int Mx,int My,uint32_t color) {
    
}

