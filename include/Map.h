#pragma once

#include "Grid.h"

class Map
{
private:
    Vector size;
    Grid<Cell> grid;
public:
    Map();
    Map(Vector size);
    Cell* operator[](int index);
    Vector getPositionFromDir(Vector currPos, Direction dir);
    bool isCellInBounds(Vector pos);
    void printWalls();
    void printVisitedMap();
    void printNeighbours(Vector pos);
};
