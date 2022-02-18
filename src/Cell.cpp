#include "Cell.h"
#include <cassert>
#include <iostream>

Cell::Cell() { }

Cell::Cell(Vector pos)
{
    this->pos = pos;
    this->visited = false;
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

void Cell::printNeighbours()
{
    std::cout << "Neighbours addresses: " << std::endl;
    for(int i = 0; i < 4; i++)
        std::cout << "Dir #" << i << ": " << neighbours[i] << std::endl;
}

bool Cell::isVisited()
{
    return visited;
}

void Cell::setVisited(bool value)
{
    visited = value;
}