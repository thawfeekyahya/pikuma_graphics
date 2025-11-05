#include "sdlwindow.h"
#include "util.h"
#include "example1.h"
#include "example2.h"
#include "example3.h"

using namespace pikuma::utility;

int main() {

    SdlWindow window;
    window.initialize();
    window.setup();

    Example* example = new Example3();
    window.attach(example);

    while (window.isRunning()) {
        window.update();
    }

    return 0;
}
