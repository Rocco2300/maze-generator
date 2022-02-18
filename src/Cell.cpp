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
    assert(index >= 0 && index <= 4);
    neighbours[index] = neighbour;
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

void Cell::printNeighbours()
{
    std::cout << "Neighbours addresses: " << std::endl;
    for(int i = 0; i < 4; i++)
        std::cout << "Dir #" << i << ": " << neighbours[i] << std::endl;
}