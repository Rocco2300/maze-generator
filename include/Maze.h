#pragma once

#include "Grid.h"
#include "Constants.h"
#include <stack>

class Maze
{
private:
    std::stack<Coord> stack;
    Grid<Cell> grid;
    Grid<uint8_t> maze;
    Coord size;
public:
    Maze();
    Maze(Coord size);
    void reset();
    void removeNeighbourSignatures(Coord coord);
    void setObstacle(Coord coord, bool value);
    void generateMaze();
    Cell* operator[](int index);
    bool isCellInBounds(Coord pos);
    void printWalls();
    void printSignatures();
    void printMaze();
    void printMaze2();
private:
    void generate(Coord coord);
    void generate2(Coord start);
    void generateViewableMaze();
    void generateViewableMaze2();
};
