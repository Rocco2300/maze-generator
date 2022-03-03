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
    std::stack<Vec2> stack;
    Grid<Cell> grid;
    Grid<uint8_t> maze;
    Vec2 size;
public:
    Maze();
    Maze(Vec2 size);
    void reset();
    void setSize(Vec2 size);
    void setObstacle(Vec2 coord);
    void generateMaze();
    void output(std::ostream& out, OutputType type);
    void load(std::istream& in);
#if DEBUG
    void printWalls();
    void printSignatures();
    void printObstacles();
    void printMazeGrid();
#endif
private:
    bool isCellInBounds(Vec2 pos);
    void generate(Vec2 start);
    void generateMazeGrid();
    void removeNeighbourSignatures(Vec2 coord);
};
