#include "example2.h"

#include "pikuma/draw.h"

namespace pikuma::examples {

void Example2::render(ColorBuffer& buffer) {
    draw_rect(buffer, 40, 70, 30, 30, kBlue);
}

}  // namespace pikuma::examples
