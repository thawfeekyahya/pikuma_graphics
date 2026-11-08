#include <cmath>

#include <gtest/gtest.h>

#include "pikuma/camera.h"
#include "pikuma/projection.h"
#include "pikuma/vector.h"

using pikuma::Camera;
using pikuma::Vector2d;
using pikuma::Vector3d;

namespace {
constexpr float kHalfPi = 1.57079632679f;
constexpr float kTolerance = 1e-5f;
}  // namespace

TEST(Vector2dTest, DefaultsToZero) {
    const Vector2d v;
    EXPECT_FLOAT_EQ(v.x, 0.0f);
    EXPECT_FLOAT_EQ(v.y, 0.0f);
}

TEST(Vector2dTest, FieldsCanBeChangedDirectly) {
    Vector2d v{1.0f, 2.0f};
    v.x += 3.0f;
    v.y = 5.0f;
    EXPECT_FLOAT_EQ(v.x, 4.0f);
    EXPECT_FLOAT_EQ(v.y, 5.0f);
}

TEST(Vector2dTest, AdditionAndSubtraction) {
    const Vector2d a{1.0f, 2.0f};
    const Vector2d b{3.0f, 4.0f};

    const Vector2d sum = a + b;
    const Vector2d diff = a - b;

    EXPECT_FLOAT_EQ(sum.x, 4.0f);
    EXPECT_FLOAT_EQ(sum.y, 6.0f);
    EXPECT_FLOAT_EQ(diff.x, -2.0f);
    EXPECT_FLOAT_EQ(diff.y, -2.0f);
}

TEST(Vector2dTest, ScalarOperationsAndDot) {
    const Vector2d v{3.0f, 4.0f};
    const Vector2d scaled = v * 2.0f;
    const Vector2d divided = v / 2.0f;

    EXPECT_FLOAT_EQ(scaled.x, 6.0f);
    EXPECT_FLOAT_EQ(scaled.y, 8.0f);
    EXPECT_FLOAT_EQ((2.0f * v).x, 6.0f);
    EXPECT_FLOAT_EQ(divided.x, 1.5f);
    EXPECT_FLOAT_EQ(divided.y, 2.0f);
    EXPECT_FLOAT_EQ(dot(v, Vector2d{1.0f, 1.0f}), 7.0f);
    EXPECT_FLOAT_EQ(v.length(), 5.0f);
}

TEST(Vector2dTest, NormalizeMakesLengthOne) {
    Vector2d v{3.0f, 4.0f};
    v.normalize();
    EXPECT_FLOAT_EQ(v.length(), 1.0f);
}

TEST(Vector2dTest, NormalizingZeroVectorLeavesItZero) {
    Vector2d v;
    v.normalize();
    EXPECT_FLOAT_EQ(v.x, 0.0f);
    EXPECT_FLOAT_EQ(v.y, 0.0f);
}

TEST(Vector3dTest, DefaultsToZero) {
    const Vector3d v;
    EXPECT_FLOAT_EQ(v.x, 0.0f);
    EXPECT_FLOAT_EQ(v.y, 0.0f);
    EXPECT_FLOAT_EQ(v.z, 0.0f);
}

TEST(Vector3dTest, AdditionAndSubtraction) {
    const Vector3d a{1.0f, 2.0f, 3.0f};
    const Vector3d b{4.0f, 5.0f, 6.0f};

    const Vector3d sum = a + b;
    const Vector3d diff = a - b;

    EXPECT_FLOAT_EQ(sum.x, 5.0f);
    EXPECT_FLOAT_EQ(sum.y, 7.0f);
    EXPECT_FLOAT_EQ(sum.z, 9.0f);
    EXPECT_FLOAT_EQ(diff.x, -3.0f);
    EXPECT_FLOAT_EQ(diff.y, -3.0f);
    EXPECT_FLOAT_EQ(diff.z, -3.0f);
}

TEST(Vector3dTest, CompoundAssignment) {
    Vector3d v{1.0f, 1.0f, 1.0f};
    v += Vector3d{1.0f, 2.0f, 3.0f};
    v *= 2.0f;
    EXPECT_FLOAT_EQ(v.x, 4.0f);
    EXPECT_FLOAT_EQ(v.y, 6.0f);
    EXPECT_FLOAT_EQ(v.z, 8.0f);
}

TEST(Vector3dTest, CrossProductFollowsRightHandRule) {
    const Vector3d x_axis{1.0f, 0.0f, 0.0f};
    const Vector3d y_axis{0.0f, 1.0f, 0.0f};

    const Vector3d result = cross(x_axis, y_axis);

    EXPECT_FLOAT_EQ(result.x, 0.0f);
    EXPECT_FLOAT_EQ(result.y, 0.0f);
    EXPECT_FLOAT_EQ(result.z, 1.0f);
}

TEST(Vector3dTest, DotAndNormalize) {
    Vector3d v{3.0f, 4.0f, 0.0f};
    EXPECT_FLOAT_EQ(dot(v, Vector3d{1.0f, 1.0f, 0.0f}), 7.0f);
    v.normalize();
    EXPECT_FLOAT_EQ(v.length(), 1.0f);
}

TEST(Vector3dTest, NormalizingZeroVectorLeavesItZero) {
    Vector3d v;
    v.normalize();
    EXPECT_FLOAT_EQ(v.x, 0.0f);
    EXPECT_FLOAT_EQ(v.y, 0.0f);
    EXPECT_FLOAT_EQ(v.z, 0.0f);
}

TEST(Vector3dTest, LengthOfConstVector) {
    const Vector3d v{1.0f, 2.0f, 3.0f};
    EXPECT_FLOAT_EQ(v.length(), std::sqrt(14.0f));
}

TEST(Vector3dTest, RotateByZeroDoesNothing) {
    const Vector3d v{1.0f, 2.0f, 3.0f};
    for (const Vector3d& r : {v.rotate_x(0.0f), v.rotate_y(0.0f), v.rotate_z(0.0f)}) {
        EXPECT_FLOAT_EQ(r.x, 1.0f);
        EXPECT_FLOAT_EQ(r.y, 2.0f);
        EXPECT_FLOAT_EQ(r.z, 3.0f);
    }
}

TEST(Vector3dTest, RotateQuarterTurn) {
    const Vector3d y_axis{0.0f, 1.0f, 0.0f};
    const Vector3d r = y_axis.rotate_x(kHalfPi);  // y -> z
    EXPECT_NEAR(r.x, 0.0f, kTolerance);
    EXPECT_NEAR(r.y, 0.0f, kTolerance);
    EXPECT_NEAR(r.z, 1.0f, kTolerance);

    const Vector3d x_axis{1.0f, 0.0f, 0.0f};
    const Vector3d rz = x_axis.rotate_z(kHalfPi);  // x -> y
    EXPECT_NEAR(rz.x, 0.0f, kTolerance);
    EXPECT_NEAR(rz.y, 1.0f, kTolerance);
}

TEST(ProjectionTest, PerspectiveDividesByDepth) {
    const Vector2d p = pikuma::project(Vector3d{1.0f, 2.0f, 4.0f}, 100.0f);
    EXPECT_FLOAT_EQ(p.x, 25.0f);
    EXPECT_FLOAT_EQ(p.y, 50.0f);
}

TEST(ProjectionTest, OrthographicIgnoresDepth) {
    const Vector2d p = pikuma::project_orthographic(Vector3d{1.0f, 2.0f, 4.0f}, 100.0f);
    EXPECT_FLOAT_EQ(p.x, 100.0f);
    EXPECT_FLOAT_EQ(p.y, 200.0f);
}

TEST(CameraTest, StoresValues) {
    const Camera camera{{1.0f, 2.0f, 3.0f}, {0.1f, 0.2f, 0.3f}, 60.0f};
    EXPECT_FLOAT_EQ(camera.position.x, 1.0f);
    EXPECT_FLOAT_EQ(camera.rotation.z, 0.3f);
    EXPECT_FLOAT_EQ(camera.fov, 60.0f);
}
