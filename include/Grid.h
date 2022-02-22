#pragma once

#include "Cell.h"

template <typename T>
class Grid
{
private:
    T** data;
    Coord size;
public:
    Grid();
    Grid(Coord size);
    Grid(const Grid& grid);
    T* operator[](int index);
    T& at(int xIndex, int yIndex);
    Grid& operator=(const Grid& grid);
    Coord getSize();
    ~Grid();
};

#include "Grid.inl"