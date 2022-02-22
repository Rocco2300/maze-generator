#pragma once

#include "Cell.h"

const Coord dirOffset[4] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

const DirFlag dirToFlag[4] = {
    DirFlag::North,
    DirFlag::East,
    DirFlag::South,
    DirFlag::West
};

const Direction oppositeDir[4] = {
    Direction::South, 
    Direction::West, 
    Direction::North, 
    Direction::East
};