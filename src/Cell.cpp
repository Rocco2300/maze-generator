#include "Cell.h"
#include <cmath>
#include <cassert>
#include <iostream>

Cell::Cell()
{
    this->walls = 15;
    this->signature = 0;
    this->obstacle = false;
}

void Cell::resetWalls()
{
    walls = 15;
}

void Cell::destroyWall(DirFlag dir)
{
    // We use 2^wallDir to get the mask of the wall
    // since we store the walls as binary 0b1111
    walls &= ~static_cast<uint8_t>(dir);
}

void Cell::addSignature(DirFlag dir)
{
    signature |= static_cast<uint8_t>(dir);
}

void Cell::removeSignature(DirFlag dir)
{
    signature &= ~static_cast<uint8_t>(dir);
}

void Cell::setSignature(uint8_t signature)
{
    this->signature = signature;
}

void Cell::setWalls(uint8_t walls)
{
    this->walls = walls;
}

void Cell::setObstacle(bool value)
{
    obstacle = value;
}

bool Cell::hasWall(DirFlag dir)
{
    return walls & (int)dir;
}

uint8_t Cell::getWalls()
{
    return walls;   
}

uint8_t Cell::getSignature()
{
    return signature;
}

bool Cell::isObstacle()
{
    return obstacle;
}