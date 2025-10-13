#include "sdlwindow.h"

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
