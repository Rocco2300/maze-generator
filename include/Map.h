#pragma once

#include "Grid.h"

class Map
{
private:
    Grid<Cell> grid;
    Vector size;
public:
    Map();
    Map(Vector size);
    Vector getSize();
    Grid<Cell>* getMapData();
    Cell* operator[](int index);
    bool isCellInBounds(Vector pos);
    void printWalls();
    void printVisitedMap();
    void printNeighbours(Vector pos);
};
