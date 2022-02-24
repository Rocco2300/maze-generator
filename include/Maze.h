#pragma once

#include "Grid.h"
#include "Constants.h"
#include <stack>

class Maze
{
private:
    std::stack<Coord> stack;
    Grid<Cell> grid;
    Coord size;
public:
    Maze();
    Maze(Coord size);
    void reset();
    void removeNeighbourSignatures(Coord coord);
    void generateMaze();
    Cell* operator[](int index);
    bool isCellInBounds(Coord pos);
    void printWalls();
    void printSignatures();
private:
    void generate(Coord coord);
    void generate2(Coord start);
};
