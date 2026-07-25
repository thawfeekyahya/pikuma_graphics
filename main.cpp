#include <memory>

#include "sdlwindow.h"
#include "example1.h"
#include "example7.h"

int main() {
    SdlWindow window;
    window.initialize();

    auto example = std::make_unique<Example7>();
    example->initialize();
    window.attach(std::move(example));

    while (window.isRunning()) {
        window.update();
    }

    return 0;
}
