#include <filesystem>
#include <memory>

#include <gtest/gtest.h>

#include "examples.h"
#include "pikuma/color_buffer.h"
#include "pikuma/sdl_window.h"

using pikuma::ColorBuffer;

namespace {

// Examples 6 and 7 load meshes from ./assets, so run from the source folder.
class ExamplesTest : public ::testing::Test {
protected:
    void SetUp() override {
        m_previous_dir = std::filesystem::current_path();
        std::filesystem::current_path(std::filesystem::path(PIKUMA_ASSETS_DIR).parent_path());
    }
    void TearDown() override { std::filesystem::current_path(m_previous_dir); }

private:
    std::filesystem::path m_previous_dir;
};

bool has_non_black_pixel(const ColorBuffer& buffer) {
    for (int y = 0; y < buffer.height(); ++y) {
        for (int x = 0; x < buffer.width(); ++x) {
            if (buffer.pixel(x, y) != pikuma::kBlack) {
                return true;
            }
        }
    }
    return false;
}

}  // namespace

TEST_F(ExamplesTest, UnknownNumberReturnsNull) {
    EXPECT_EQ(pikuma::examples::make_example(0), nullptr);
    EXPECT_EQ(pikuma::examples::make_example(pikuma::examples::kLatestExample + 1), nullptr);
}

// Runs a few frames of every example without a window and checks that something is drawn.
TEST_F(ExamplesTest, EveryExampleDrawsSomething) {
    constexpr int kWidth = 320;
    constexpr int kHeight = 240;

    for (int number = 1; number <= pikuma::examples::kLatestExample; ++number) {
        SCOPED_TRACE(number);
        auto example = pikuma::examples::make_example(number);
        ASSERT_NE(example, nullptr);
        EXPECT_FALSE(example->title().empty());

        ColorBuffer buffer(kWidth, kHeight);
        example->setup(kWidth, kHeight);
        for (int frame = 0; frame < 3; ++frame) {
            example->update();
            buffer.clear(pikuma::kBlack);
            example->render(buffer);
        }
        EXPECT_TRUE(has_non_black_pixel(buffer));
    }
}

TEST(SdlWindowTest, IsNotRunningBeforeInitialize) {
    const pikuma::SdlWindow window;
    EXPECT_FALSE(window.is_running());
}
