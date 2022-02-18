#pragma once

#include <stdint.h>
#include <vector>

struct Vector
{
    int x, y;
};

enum Direction
{
    N = 0,
    E,
    S,
    W
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
    bool isVisited();
    void setVisited(bool value);
    uint8_t getWalls();
    void destroyWall(Direction dir);
    void printNeighbours();
};