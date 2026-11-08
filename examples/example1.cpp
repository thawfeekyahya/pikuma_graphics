#include "example1.h"

#include "pikuma/draw.h"

namespace pikuma::examples {

void Example1::render(ColorBuffer& buffer) {
    draw_grid(buffer, 10, kRed);
}

}  // namespace pikuma::examples
