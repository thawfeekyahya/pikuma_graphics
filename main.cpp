#include "sdlwindow.h"
#include "util.h"


using namespace pikuma::utility;

int main() {

    SdlWindow window;
    window.initialize();
    window.setup();

    while (window.isRunning()) {
        window.process_input();
        window.update();
        window.render();
    }
    return 0;
}
