#pragma once

#include "Grid.h"
#include "Constants.h"
#include <stack>

#define DEBUG false

enum class OutputType
{
    Data,
    Maze
};

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
    void setObstacle(Coord coord);
    void generateMaze();
    void output(std::ostream& out, OutputType type);
#if DEBUG
    Cell* operator[](int index);
    void printWalls();
    void printSignatures();
    void printObstacles();
    void printMazeGrid();
#endif
private:
    bool isCellInBounds(Coord pos);
    void generate(Coord start);
    void generateMazeGrid();
    void removeNeighbourSignatures(Coord coord);
};
