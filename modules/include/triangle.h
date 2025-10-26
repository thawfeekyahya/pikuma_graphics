# pragma once
#include "util.h"
#include <vector>

class Face{
public:
    Face(int _a,int _b,int _c);
    Face();

    int get_a() const { return a; }
    int get_b() const { return b; }
    int get_c() const { return c; }

private:
    int a;
    int b;
    int c;
};


class Triangle {
public:
    std::vector<pikuma::utility::Vector2d> points{3};
};
