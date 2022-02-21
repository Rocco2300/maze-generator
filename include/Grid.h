#pragma once

#include "Cell.h"

template <typename T>
class Grid
{
private:
    T** data;
    Vector size;
public:
    Grid();
    Grid(Vector size);
    Grid(const Grid& grid);
    T* operator[](int index);
    T& at(int xIndex, int yIndex);
    Grid& operator=(const Grid& grid);
    Vector getSize();
    ~Grid();
};

#include "Grid.inl"