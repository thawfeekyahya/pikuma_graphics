#include "examples.h"

#include "example1.h"
#include "example2.h"
#include "example3.h"
#include "example4.h"
#include "example5.h"
#include "example6.h"
#include "example7.h"

namespace pikuma::examples {

std::unique_ptr<Example> make_example(int number) {
    switch (number) {
        case 1: return std::make_unique<Example1>();
        case 2: return std::make_unique<Example2>();
        case 3: return std::make_unique<Example3>();
        case 4: return std::make_unique<Example4>();
        case 5: return std::make_unique<Example5>();
        case 6: return std::make_unique<Example6>();
        case 7: return std::make_unique<Example7>();
        default: return nullptr;
    }
}

}  // namespace pikuma::examples
