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
    Vector getPositionFromDir(Vector currPos, Direction dir);
    bool isCellInBounds(Vector pos);
    void printVisitedMap();
    void printNeighbours(Vector pos);
};
