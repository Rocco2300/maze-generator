#pragma once

#include "Cell.h"
#include <vector>
#include <array>

const Coord dirOffset[4] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

constexpr DirFlag dirToFlag[4] = {
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

struct Data
{
    std::array<Direction, 4> data = {};
    int size;
};

constexpr std::array<Data, 16> buildRandDirTable()
{
    std::array<Data, 16> result = {};

    for(int i = 0; i < 16; i++)
    {
        int cnt = 0;
        int index = 0;
        for(int dir = 0; dir < 4; dir++)
        {
            if(i & (int)dirToFlag[dir])
            {
                result[i].data[index++] = (Direction)dir;
                continue;
            }
            cnt++;
        }

        for(int j = index; j < cnt; j++)
        {
            result[i].data[j] = Direction::NONE;
        }
        result[i].size = index;
    }

    return result;
}

const std::array<Data, 16> randDirTable = buildRandDirTable();