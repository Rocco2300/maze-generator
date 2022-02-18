#pragma once

#include "Cell.h"

class Grid
{
private:
    Vector size;
    Cell** data;
public:
    Grid();
    Grid(Vector size);
    Cell* operator[](int index);
    ~Grid();
};
