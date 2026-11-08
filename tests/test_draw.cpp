#include <gtest/gtest.h>

#include "pikuma/color_buffer.h"
#include "pikuma/draw.h"

using pikuma::ColorBuffer;
using pikuma::kBlack;
using pikuma::kRed;

namespace {
int count_pixels(const ColorBuffer& buffer, pikuma::Color color) {
    int count = 0;
    for (int y = 0; y < buffer.height(); ++y) {
        for (int x = 0; x < buffer.width(); ++x) {
            if (buffer.pixel(x, y) == color) {
                ++count;
            }
        }
    }
    return count;
}
}  // namespace

TEST(ColorBufferTest, StartsBlackWithGivenSize) {
    const ColorBuffer buffer(4, 3);
    EXPECT_EQ(buffer.width(), 4);
    EXPECT_EQ(buffer.height(), 3);
    EXPECT_EQ(buffer.pitch_bytes(), 16);
    EXPECT_EQ(count_pixels(buffer, kBlack), 12);
}

TEST(ColorBufferTest, ClearFillsEveryPixel) {
    ColorBuffer buffer(2, 2);
    buffer.clear(kRed);
    EXPECT_EQ(count_pixels(buffer, kRed), 4);
}

TEST(ColorBufferTest, OutOfBoundsPixelsAreIgnored) {
    ColorBuffer buffer(2, 2);
    buffer.set_pixel(-1, 0, kRed);
    buffer.set_pixel(0, 2, kRed);
    buffer.set_pixel(2, 0, kRed);
    EXPECT_EQ(count_pixels(buffer, kRed), 0);
}

TEST(DrawTest, ZeroLengthLineDrawsOnePixel) {
    ColorBuffer buffer(3, 3);
    pikuma::draw_line(buffer, 1, 1, 1, 1, kRed);
    EXPECT_EQ(buffer.pixel(1, 1), kRed);
    EXPECT_EQ(count_pixels(buffer, kRed), 1);
}

TEST(DrawTest, HorizontalLineIncludesBothEnds) {
    ColorBuffer buffer(10, 3);
    pikuma::draw_line(buffer, 2, 1, 7, 1, kRed);
    EXPECT_EQ(count_pixels(buffer, kRed), 6);
    EXPECT_EQ(buffer.pixel(2, 1), kRed);
    EXPECT_EQ(buffer.pixel(7, 1), kRed);
}

TEST(DrawTest, DiagonalLine) {
    ColorBuffer buffer(5, 5);
    pikuma::draw_line(buffer, 0, 0, 4, 4, kRed);
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(buffer.pixel(i, i), kRed);
    }
    EXPECT_EQ(count_pixels(buffer, kRed), 5);
}

TEST(DrawTest, RectIsClippedToBuffer) {
    ColorBuffer buffer(4, 4);
    pikuma::draw_rect(buffer, 2, 2, 10, 10, kRed);
    EXPECT_EQ(count_pixels(buffer, kRed), 4);
}

TEST(DrawTest, GridDrawsEveryNthRowAndColumn) {
    ColorBuffer buffer(5, 5);
    pikuma::draw_grid(buffer, 2, kRed);
    EXPECT_EQ(buffer.pixel(0, 1), kRed);
    EXPECT_EQ(buffer.pixel(1, 2), kRed);
    EXPECT_EQ(buffer.pixel(1, 1), kBlack);
    EXPECT_EQ(buffer.pixel(3, 3), kBlack);
}

TEST(DrawTest, FilledTriangleCoversInsideButNotOutside) {
    ColorBuffer buffer(20, 20);
    // Vertex order does not matter; draw_filled_triangle sorts by y.
    pikuma::draw_filled_triangle(buffer, 10, 18, 2, 2, 18, 10, kRed);

    EXPECT_EQ(buffer.pixel(10, 10), kRed);  // inside
    EXPECT_EQ(buffer.pixel(1, 18), kBlack);  // outside
    EXPECT_EQ(buffer.pixel(18, 2), kBlack);  // outside
}

TEST(DrawTest, FlatBottomAndFlatTopTriangles) {
    ColorBuffer flat_bottom(10, 10);
    pikuma::draw_filled_triangle(flat_bottom, 5, 0, 0, 8, 9, 8, kRed);
    EXPECT_EQ(flat_bottom.pixel(5, 6), kRed);

    ColorBuffer flat_top(10, 10);
    pikuma::draw_filled_triangle(flat_top, 0, 0, 9, 0, 5, 8, kRed);
    EXPECT_EQ(flat_top.pixel(5, 2), kRed);
}

TEST(DrawTest, ZeroHeightTriangleDoesNotCrash) {
    ColorBuffer buffer(10, 10);
    pikuma::draw_filled_triangle(buffer, 1, 5, 4, 5, 8, 5, kRed);
    SUCCEED();
}
