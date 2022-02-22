#pragma once

#include "Grid.h"
#include "Constants.h"

class Maze
{
private:
    Grid<Cell> grid;
    Coord size;
public:
    Maze();
    Maze(Coord size);
    Coord getSize();
    Cell* operator[](int index);
    bool isCellInBounds(Coord pos);
    void printWalls();
    void printSignatures();
};
