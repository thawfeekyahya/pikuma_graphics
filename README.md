# Pikuma 3D graphics from scratch (C++)

A software renderer built step by step while following the Pikuma 3D graphics course.
Each step of the course is its own `ExampleN` class.

## Build and run

```sh
cmake -S . -B build
cmake --build build -j
cd build
./pikuma        # runs the latest example
./pikuma 4      # runs Example4
ctest           # runs the unit tests
```

Press `Esc` to quit.

## Layout

```
modules/                Shared code, used by every example (library: pikuma_core)
  include/pikuma/
    vector.h            Vector2d / Vector3d   (vec2_t / vec3_t in the course)
    mesh.h              Face, Mesh, cube data, load_obj_file   (mesh.c)
    triangle.h          Triangle   (triangle_t)
    projection.h        project()
    color_buffer.h      ColorBuffer and Color constants
    draw.h              draw_pixel, draw_line, draw_triangle, draw_filled_triangle, ...   (display.c / triangle.c)
    camera.h            Camera
    example.h           Example base class
    sdl_window.h        SDL window and main loop
examples/               One class per course step (library: examples)
  exampleN.h / .cpp
  examples.h / .cpp     kLatestExample and make_example(number)
tests/                  GoogleTest unit tests
assets/                 .obj models, copied next to the executable at build time
```

## Course C code vs this code

| Course (C)                     | Here (C++)                          |
|--------------------------------|-------------------------------------|
| `vec3_t v; v.x = 1;`           | `Vector3d v; v.x = 1;`              |
| `vec3_add(a, b)` / `vec3_sub`  | `a + b` / `a - b`                   |
| `vec3_mul(v, s)` / `vec3_div`  | `v * s` / `v / s`                   |
| `vec3_cross(a, b)`             | `cross(a, b)`                       |
| `vec3_dot(a, b)`               | `dot(a, b)`                         |
| `vec3_normalize(&v)`           | `v.normalize()`                     |
| `vec3_rotate_x(v, angle)`      | `v.rotate_x(angle)`                 |
| `draw_line(x0, y0, x1, y1, c)` | `draw_line(buffer, x0, y0, x1, y1, c)` |
| `setup()`                      | `on_setup()`                        |
| `process_input()`              | `on_key_down(key)`                  |
| `update()` / `render()`        | `update()` / `render(buffer)`       |

## Adding the next example

1. Copy `examples/example7.h` / `.cpp` to `example8.h` / `.cpp`, then rename the class and title.
2. Add a `case 8:` to `make_example()` in `examples/examples.cpp` and set `kLatestExample = 8`
   in `examples/examples.h`.
3. Re-run `cmake --build build`. New `.cpp` files in `examples/` are picked up automatically.

If the course adds a new drawing function or math helper, put it in `modules/` so later
examples can use it too.

## Code style

- Types are `PascalCase`. Functions and variables are `snake_case`.
- Private class members start with `m_`. Constants start with `k`.
- Simple data types (`Vector3d`, `Face`, `Mesh`, `Triangle`) are structs with public fields.
- Everything is in namespace `pikuma` (examples are in `pikuma::examples`).
