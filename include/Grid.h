#pragma once

#include "Cell.h"

template <typename T>
class Grid
{
private:
    Vector size;
    T** data;
public:
    Grid();
    Grid(Vector size);
    T* operator[](int index);
    Grid& operator=(const Grid& grid);
    ~Grid();
};

#include "Grid.inl"