#pragma once

#include "Cell.h"
#include <vector>
#include <array>

const Coord dirOffset[4] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
const Coord cornerDirOffset[4] = {{-1, -1}, {1, -1}, {1, 1}, {-1, 1}};

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

constexpr std::array<uint8_t, 16> buildRandDirTableSizes()
{
    std::array<uint8_t, 16> result = {};

    for(int i = 0; i < 16; i++)
    {
        int cnt = 0;

        for(int dir = 0; dir < 4; dir++)
        {
            if(i & (int)dirToFlag[dir])
                cnt++;
        }
        
        result[i] = cnt;
    }

    return result;
}

constexpr std::array<uint8_t, 16> randDirTableSizes = buildRandDirTableSizes();

constexpr std::array<std::array<Direction, 4>, 16> buildRandDirTable()
{
    std::array<std::array<Direction, 4>, 16> result = {};

    for(int i = 0; i < 16; i++)
    {
        int index = 0;
        for(int dir = 0; dir < 4; dir++)
        {
            /*
            (1)
            Find all available signatures in i
            and store them, also count the number
            of all the unavilable directions
            */
            if(i & (int)dirToFlag[dir])
            {
                result[i][index++] = (Direction)dir;
                continue;
            }
        }

        // Buffer the unused space with garbage data
        for(int j = index; j < 4; j++)
        {
            result[i][j] = Direction::North;
        }
    }

    return result;
}

const std::array<std::array<Direction, 4>, 16> randDirTable = buildRandDirTable();