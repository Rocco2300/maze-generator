#pragma once

#include <cassert>
#include <cstdint>
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
    Cell** getNeighbours();
    void removeNeighbour(Cell* neighbour);
    void removeFromNeighbours();
    bool isVisited();
    void setVisited(bool value);
    uint8_t getWalls();
    void destroyWall(Direction dir);
    Vector getPositionFromDir(Direction dir);
    void printNeighbours();
};