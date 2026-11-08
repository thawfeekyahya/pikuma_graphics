#pragma once

// 2D and 3D vector types.
//
// These are plain structs with public x/y/z, the same as `vec2_t`/`vec3_t` in the
// course's C code, so `v.x += 1.0f;` works directly. The C helper functions map like this:
//   vec3_add(a, b)      -> a + b
//   vec3_sub(a, b)      -> a - b
//   vec3_mul(v, s)      -> v * s
//   vec3_div(v, s)      -> v / s
//   vec3_cross(a, b)    -> cross(a, b)
//   vec3_dot(a, b)      -> dot(a, b)
//   vec3_length(v)      -> v.length()
//   vec3_normalize(&v)  -> v.normalize()
//   vec3_rotate_x(v, a) -> v.rotate_x(a)

namespace pikuma {

////////////////////////////////////////////////////////////////////////////////
// Vector2d
////////////////////////////////////////////////////////////////////////////////

struct Vector2d {
    float x = 0.0f;
    float y = 0.0f;

    [[nodiscard]] float length() const;
    void normalize();

    constexpr Vector2d& operator+=(const Vector2d& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    constexpr Vector2d& operator-=(const Vector2d& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    constexpr Vector2d& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }
    constexpr Vector2d& operator/=(float scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }
};

[[nodiscard]] constexpr Vector2d operator+(Vector2d a, const Vector2d& b) { return a += b; }
[[nodiscard]] constexpr Vector2d operator-(Vector2d a, const Vector2d& b) { return a -= b; }
[[nodiscard]] constexpr Vector2d operator*(Vector2d v, float scalar) { return v *= scalar; }
[[nodiscard]] constexpr Vector2d operator*(float scalar, Vector2d v) { return v *= scalar; }
[[nodiscard]] constexpr Vector2d operator/(Vector2d v, float scalar) { return v /= scalar; }

[[nodiscard]] constexpr float dot(const Vector2d& a, const Vector2d& b) {
    return (a.x * b.x) + (a.y * b.y);
}

////////////////////////////////////////////////////////////////////////////////
// Vector3d
////////////////////////////////////////////////////////////////////////////////

struct Vector3d {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

    [[nodiscard]] float length() const;
    void normalize();

    // Rotation around one axis. Angles are in radians. Each returns a new vector.
    [[nodiscard]] Vector3d rotate_x(float angle) const;
    [[nodiscard]] Vector3d rotate_y(float angle) const;
    [[nodiscard]] Vector3d rotate_z(float angle) const;

    constexpr Vector3d& operator+=(const Vector3d& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }
    constexpr Vector3d& operator-=(const Vector3d& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }
    constexpr Vector3d& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }
    constexpr Vector3d& operator/=(float scalar) {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }
};

[[nodiscard]] constexpr Vector3d operator+(Vector3d a, const Vector3d& b) { return a += b; }
[[nodiscard]] constexpr Vector3d operator-(Vector3d a, const Vector3d& b) { return a -= b; }
[[nodiscard]] constexpr Vector3d operator*(Vector3d v, float scalar) { return v *= scalar; }
[[nodiscard]] constexpr Vector3d operator*(float scalar, Vector3d v) { return v *= scalar; }
[[nodiscard]] constexpr Vector3d operator/(Vector3d v, float scalar) { return v /= scalar; }

[[nodiscard]] constexpr float dot(const Vector3d& a, const Vector3d& b) {
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

[[nodiscard]] constexpr Vector3d cross(const Vector3d& a, const Vector3d& b) {
    return {
        (a.y * b.z) - (a.z * b.y),
        (a.z * b.x) - (a.x * b.z),
        (a.x * b.y) - (a.y * b.x),
    };
}

}  // namespace pikuma
