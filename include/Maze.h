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
    void removeNeighbourSignatures(Coord coord);
    void generateMaze();
    Cell* operator[](int index);
    bool isCellInBounds(Coord pos);
    void printWalls();
    void printSignatures();
private:
    void generate(Coord coord);
};
