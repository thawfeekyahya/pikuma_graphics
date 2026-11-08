#include <filesystem>
#include <fstream>
#include <string>

#include <gtest/gtest.h>

#include "pikuma/mesh.h"

using pikuma::Face;
using pikuma::Mesh;

TEST(MeshTest, CanStoreVerticesAndFaces) {
    Mesh mesh;
    mesh.vertices.push_back({1.0f, 2.0f, 3.0f});
    mesh.faces.push_back(Face{1, 2, 3});

    ASSERT_EQ(mesh.vertices.size(), 1U);
    EXPECT_EQ(mesh.faces.size(), 1U);
    EXPECT_EQ(mesh.faces.front().a, 1);
}

TEST(MeshTest, CubeMeshHasEightVerticesAndTwelveFaces) {
    const Mesh mesh = pikuma::load_cube_mesh();
    EXPECT_EQ(mesh.vertices.size(), 8U);
    EXPECT_EQ(mesh.faces.size(), 12U);
}

TEST(MeshTest, CubeFaceIndicesAreOneBasedAndInRange) {
    for (const Face& face : pikuma::kCubeFaces) {
        for (int index : {face.a, face.b, face.c}) {
            EXPECT_GE(index, 1);
            EXPECT_LE(index, static_cast<int>(pikuma::kCubeVertexCount));
        }
    }
}

TEST(ObjLoaderTest, MissingFileReturnsNullopt) {
    EXPECT_FALSE(pikuma::load_obj_file("does/not/exist.obj").has_value());
}

TEST(ObjLoaderTest, LoadsCubeAsset) {
    const auto mesh = pikuma::load_obj_file(std::string(PIKUMA_ASSETS_DIR) + "/cube.obj");
    ASSERT_TRUE(mesh.has_value());
    EXPECT_EQ(mesh->vertices.size(), 8U);
    EXPECT_EQ(mesh->faces.size(), 12U);
}

TEST(ObjLoaderTest, ParsesAllFaceTokenFormats) {
    const auto path = std::filesystem::temp_directory_path() / "pikuma_test_faces.obj";
    {
        std::ofstream out(path);
        out << "# comment\n"
               "v 1.0 2.0 3.0\n"
               "v 4 5 6\n"
               "v 7 8 9\n"
               "f 1 2 3\n"
               "f 1/1 2/2 3/3\n"
               "f 1//1 2//2 3//3\n"
               "f 3/1/1 2/2/2 1/3/3\n";
    }

    const auto mesh = pikuma::load_obj_file(path.string());
    std::filesystem::remove(path);

    ASSERT_TRUE(mesh.has_value());
    ASSERT_EQ(mesh->vertices.size(), 3U);
    EXPECT_FLOAT_EQ(mesh->vertices[0].x, 1.0f);
    EXPECT_FLOAT_EQ(mesh->vertices[2].z, 9.0f);

    ASSERT_EQ(mesh->faces.size(), 4U);
    EXPECT_EQ(mesh->faces[0].a, 1);
    EXPECT_EQ(mesh->faces[2].c, 3);
    EXPECT_EQ(mesh->faces[3].a, 3);
    EXPECT_EQ(mesh->faces[3].c, 1);
}
