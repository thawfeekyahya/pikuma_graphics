#include "sdlwindow.h"
#include "util.h"
#include "example1.h"

using namespace pikuma::utility;

int main() {

    SdlWindow window;
    window.initialize();
    window.setup();

    Example* example = new Example1();
    window.attach(example);

    while (window.isRunning()) {
        window.update();
    }
    return 0;
}
