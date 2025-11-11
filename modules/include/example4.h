#pragma once

#include "example3.h"
#include "util.h"
#include <vector>

class Example4: public Example3 {
public:
    Example4();
    void initialize() override;
    void update() override;
    void render() override;
    void process_input() override;
private:
    std::vector<pikuma::utility::Vector3d> cube_vertices;
    std::vector<pikuma::utility::Face>  cube_faces;
};
