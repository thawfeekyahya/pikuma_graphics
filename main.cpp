// Usage: ./pikuma [example-number]
// With no number, runs the latest example (kLatestExample in examples/examples.h).

#include <cstdlib>
#include <iostream>
#include <string>

#include "examples.h"
#include "pikuma/sdl_window.h"

int main(int argc, char* argv[]) {
    int example_number = pikuma::examples::kLatestExample;
    if (argc > 1) {
        example_number = std::atoi(argv[1]);
    }

    auto example = pikuma::examples::make_example(example_number);
    if (!example) {
        std::cerr << "Unknown example: " << (argc > 1 ? argv[1] : "") << '\n';
        return EXIT_FAILURE;
    }

    pikuma::SdlWindow window;
    if (!window.initialize()) {
        return EXIT_FAILURE;
    }

    window.run(*example);
    return EXIT_SUCCESS;
}
