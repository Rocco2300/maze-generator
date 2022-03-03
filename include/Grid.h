#pragma once

#include "Cell.h"

template <typename T>
class Grid
{
private:
    T* data;
    Vec2 size;
public:
    Grid();
    Grid(Vec2 size);
    T& operator()(int x, int y);
    T& operator()(const Vec2& c);
    Grid& operator=(const Grid& grid);
    Vec2 getSize();
    ~Grid();
};

#include "Grid.inl"