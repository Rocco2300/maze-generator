#include "Cell.h"
#include <cmath>
#include <cassert>
#include <iostream>

Cell::Cell() { }

Cell::Cell(Coord pos)
{
    this->pos = pos;
    this->walls = 15;
    this->signature = 0;
}

Coord Cell::getPosition()
{
    return pos;
}

uint8_t Cell::getWalls()
{
    return walls;   
}

uint8_t Cell::getSignature()
{
    return signature;
}

void Cell::destroyWall(Direction dir)
{
    // We use 2^wallDir to get the mask of the wall
    // since we store the walls as binary 0b1111
    uint8_t wallDir = std::pow(2, (uint8_t)dir);
    walls &= ~wallDir;
}

void Cell::addSignature(DirFlag dir)
{
    signature |= static_cast<uint8_t>(dir);
}

void Cell::removeSignature(DirFlag dir)
{
    signature &= ~static_cast<uint8_t>(dir);
}

std::ostream& operator<<(std::ostream& out, const Coord& coord)
{
    out << "(" << coord.x << ", " << coord.y << ")";
    return out;
}   