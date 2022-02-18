#pragma once

#include "Grid.h"

class Map
{
private:
    Vector size;
    Grid grid;
public:
    Map();
    Map(Vector size);
};
