#pragma once

#include <stdint.h>
#include <vector>

struct Vector
{
    int x, y;
};

enum WallDirection
{
    North = 0,
    East = 1,
    South = 2,
    West = 3
};

enum Direction
{
    Up = 0,
    Right,
    Down,
    Left
};

class Cell
{
private:
    Vector pos;
    bool visited;
    Cell* neighbours[4];
    uint8_t walls;
public:
    Cell();
    Cell(Vector pos);
    void setNeighbour(int index, Cell* neighbour);
    void printNeighbours();
    bool isVisited();
    void setVisited(bool value);
};