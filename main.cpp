#include "sdlwindow.h"
#include "util.h"
#include "example1.h"
#include "example2.h"
#include "example3.h"
#include "example4.h"

using namespace pikuma::utility;

int main() {

    SdlWindow window;
    window.initialize();
    window.setup();

    Example* example = new Example4();
    example->initialize();
    window.attach(example);

    while (window.isRunning()) {
        window.update();
    }

    return 0;
}
