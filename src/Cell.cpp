#include "Cell.h"
#include <cmath>
#include <cassert>
#include <iostream>

Cell::Cell() { }

Cell::Cell(Vector pos)
{
    this->pos = pos;
    this->visited = false;
    this->walls = 15;
    for(int i = 0; i < 4; i++)
    {
        neighbours[i] = nullptr;
    }
}

void Cell::setNeighbour(int index, Cell* neighbour)
{
    assert(index >= 0 && index < 4);
    neighbours[index] = neighbour;
}

Cell** Cell::getNeighbours()
{
    return neighbours;
}

void Cell::removeNeighbour(Cell* neighbour)
{
    for(int i = 0; i < 4; i++)
    {
        if(neighbours[i] == neighbour)
            neighbours[i] = nullptr;
    }
}

void Cell::removeFromNeighbours()
{
    for(int i = 0; i < 4; i++)
    {
        if(neighbours[i] != nullptr)
            neighbours[i]->removeNeighbour(this);
    }
}

bool Cell::isVisited()
{
    return visited;
}

void Cell::setVisited(bool value)
{
    visited = value;
}

uint8_t Cell::getWalls()
{
    return walls;   
}

void Cell::destroyWall(Direction dir)
{
    // We use 2^wallDir to get the mask of the wall
    // since we store the walls as binary 0b1111
    uint8_t wallDir = std::pow(2, (uint8_t)dir);
    walls &= ~wallDir;
}

Vector Cell::getPositionFromDir(Direction dir)
{
    // Due to the fact the we invert x and y to make traversing 
    // the matrix more logical in cartesian coordinates, we have to
    // invert the result so as res(x, y) = currentPos(y, x)
    Vector res;
    switch(dir)
    {
    case N:
        res.x = pos.y;
        res.y = pos.x - 1;
        break;
    case E:
        res.x = pos.y + 1;
        res.y = pos.x;
        break;
    case S:
        res.x = pos.y;
        res.y = pos.x + 1;
        break;
    case W:
        res.x = pos.y - 1;
        res.y = pos.x;
        break;
    }
    return res;
}


void Cell::printNeighbours()
{
    std::cout << "Neighbours addresses: " << std::endl;
    for(int i = 0; i < 4; i++)
        std::cout << "Dir #" << i << ": " << neighbours[i] << std::endl;
}