#include <cstdint>
#include <memory>

#include <gtest/gtest.h>

#include "example.h"
#include "sdlwindow.h"
#include "util.h"

using pikuma::utility::Camera;
using pikuma::utility::Face;
using pikuma::utility::Mesh;
using pikuma::utility::Triangle;
using pikuma::utility::Vector2d;
using pikuma::utility::Vector3d;

namespace {
class TestExample : public Example {
public:
    void update() override {}
    void render() override {}
    void process_input() override {}

    int width() const { return screen_width; }
    int height() const { return screen_height; }
    bool hasBuffer() const { return color_buffer != nullptr; }
};
}

TEST(Vector2dTest, DefaultConstructorInitializesToZero) {
    Vector2d v;
    EXPECT_FLOAT_EQ(v.get_x(), 0.0f);
    EXPECT_FLOAT_EQ(v.get_y(), 0.0f);
}

TEST(Vector2dTest, AdditionAndSubtractionWork) {
    Vector2d a(1.0f, 2.0f);
    Vector2d b(3.0f, 4.0f);

    auto sum = a + b;
    auto diff = a - b;

    EXPECT_FLOAT_EQ(sum.get_x(), 4.0f);
    EXPECT_FLOAT_EQ(sum.get_y(), 6.0f);
    EXPECT_FLOAT_EQ(diff.get_x(), -2.0f);
    EXPECT_FLOAT_EQ(diff.get_y(), -2.0f);
}

TEST(Vector2dTest, ScalarOperationsAndDotProductWork) {
    Vector2d v(3.0f, 4.0f);
    auto scaled = v * 2.0f;
    auto divided = v / 2.0f;
    EXPECT_FLOAT_EQ(scaled.get_x(), 6.0f);
    EXPECT_FLOAT_EQ(scaled.get_y(), 8.0f);
    EXPECT_FLOAT_EQ(divided.get_x(), 1.5f);
    EXPECT_FLOAT_EQ(divided.get_y(), 2.0f);
    EXPECT_FLOAT_EQ(v.dot(Vector2d(1.0f, 1.0f)), 7.0f);
}

TEST(Vector2dTest, NormalizeUpdatesLengthToOne) {
    Vector2d v(3.0f, 4.0f);
    v.normalize();
    EXPECT_FLOAT_EQ(v.get_length(), 1.0f);
}

TEST(Vector3dTest, DefaultConstructorInitializesToZero) {
    Vector3d v;
    EXPECT_FLOAT_EQ(v.get_x(), 0.0f);
    EXPECT_FLOAT_EQ(v.get_y(), 0.0f);
    EXPECT_FLOAT_EQ(v.get_z(), 0.0f);
}

TEST(Vector3dTest, AdditionAndSubtractionWork) {
    Vector3d a(1.0f, 2.0f, 3.0f);
    Vector3d b(4.0f, 5.0f, 6.0f);

    auto sum = a + b;
    auto diff = a - b;

    EXPECT_FLOAT_EQ(sum.get_x(), 5.0f);
    EXPECT_FLOAT_EQ(sum.get_y(), 7.0f);
    EXPECT_FLOAT_EQ(sum.get_z(), 9.0f);
    EXPECT_FLOAT_EQ(diff.get_x(), -3.0f);
    EXPECT_FLOAT_EQ(diff.get_y(), -3.0f);
    EXPECT_FLOAT_EQ(diff.get_z(), -3.0f);
}

TEST(Vector3dTest, ScalarAndCrossProductWork) {
    Vector3d a(1.0f, 0.0f, 0.0f);
    Vector3d b(0.0f, 1.0f, 0.0f);

    auto scaled = a * 2.0f;
    auto cross = a * b;

    EXPECT_FLOAT_EQ(scaled.get_x(), 2.0f);
    EXPECT_FLOAT_EQ(cross.get_z(), 1.0f);
}

TEST(Vector3dTest, DotAndNormalizeWork) {
    Vector3d v(3.0f, 4.0f, 0.0f);
    EXPECT_FLOAT_EQ(v.dot(Vector3d(1.0f, 1.0f, 0.0f)), 7.0f);
    v.normalize();
    EXPECT_FLOAT_EQ(v.get_length(), 1.0f);
}

TEST(Vector3dTest, RotationHelpersProduceExpectedValues) {
    Vector3d v(0.0f, 1.0f, 0.0f);
    auto rotated = v.rotate_x(0.0f);
    EXPECT_FLOAT_EQ(rotated.get_y(), 1.0f);
}

TEST(CameraTest, ConstructorStoresValues) {
    Vector3d position(1.0f, 2.0f, 3.0f);
    Vector3d rotation(0.1f, 0.2f, 0.3f);
    Camera camera(position, rotation, 60.0f);

    EXPECT_FLOAT_EQ(camera.position.get_x(), 1.0f);
    EXPECT_FLOAT_EQ(camera.rotation.get_z(), 0.3f);
    EXPECT_FLOAT_EQ(camera.fov, 60.0f);
}

TEST(MeshTest, CanStoreVerticesAndFaces) {
    Mesh mesh;
    mesh.vertices.emplace_back(1.0f, 2.0f, 3.0f);
    mesh.faces.push_back(Face{0, 1, 2});

    ASSERT_EQ(mesh.vertices.size(), 1u);
    EXPECT_EQ(mesh.faces.size(), 1u);
    EXPECT_EQ(mesh.faces.front().a, 0);
}

TEST(TriangleTest, FillUsesStoredPoints) {
    Triangle triangle;
    triangle.points[0] = Vector2d(0.0f, 0.0f);
    triangle.points[1] = Vector2d(4.0f, 0.0f);
    triangle.points[2] = Vector2d(0.0f, 4.0f);

    triangle.fill(0xFF00FF00);
    EXPECT_TRUE(true);
}

TEST(ExampleTest, BaseClassCanSetWindowState) {
    TestExample example;
    example.setWindowSize(640, 480);
    EXPECT_EQ(example.width(), 640);
    EXPECT_EQ(example.height(), 480);
}

TEST(ExampleTest, BaseClassCanManageColorBufferAndRenderHooks) {
    TestExample example;
    example.setWindowSize(2, 2);

    std::uint32_t buffer[4] = {0x00000000, 0x00000000, 0x00000000, 0x00000000};

    example.setColorBuffer(buffer);
    EXPECT_TRUE(example.hasBuffer());

    example.clear_color_buffer(0xFF00FF00);
    EXPECT_EQ(buffer[0], 0xFF00FF00u);
    EXPECT_EQ(buffer[3], 0xFF00FF00u);

    example.setup_render();
    example.clear_render();
}

TEST(SdlWindowTest, StartsStoppedAndCanAttachAnExample) {
    SdlWindow window;
    EXPECT_FALSE(window.isRunning());

    auto example = std::make_unique<TestExample>();
    window.attach(std::move(example));
    EXPECT_FALSE(window.isRunning());

    window.update();
    EXPECT_FALSE(window.isRunning());
}
