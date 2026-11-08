#pragma once

#include <memory>

#include "pikuma/example.h"

namespace pikuma::examples {

// The example that runs when no number is given on the command line.
// Update this when you add a new example.
inline constexpr int kLatestExample = 7;

// Creates example `number` (1 = Example1, ...). Returns nullptr for an unknown number.
[[nodiscard]] std::unique_ptr<Example> make_example(int number);

}  // namespace pikuma::examples
