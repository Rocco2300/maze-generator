#include "Maze.h"
#include <iostream>

Maze::Maze()
{
}

Maze::Maze(Coord size)
{
    this->size = size;
    grid = Grid<Cell>(size);

    for(int y = 0; y < size.y; y++)
    {
        for(int x = 0; x < size.x; x++)
        {
            Coord currentCoord(y, x);
            grid[y][x] = Cell(currentCoord);

            for(int dir = 0; dir < 4; dir++)
            {
                Coord nextCoord = currentCoord + dirOffset[dir];
                if(isCellInBounds(nextCoord))
                {
                    grid[y][x].updateSignature(dirToFlag[dir]);
                }
            }
        }
    }
}

Coord Maze::getSize()
{
    return size;
}

Cell* Maze::operator[](int index)
{
    return grid[index];
}

void Maze::printWalls()
{
    for(int y = 0; y < size.y; y++)
    {
        for(int x = 0; x < size.x; x++)
        {
            std::cout << (int)grid[y][x].getWalls() << " ";
        }
        std::cout << std::endl;
    }
}

bool Maze::isCellInBounds(Coord pos)
{
    return pos.x >= 0 && pos.x < size.y && pos.y >= 0 && pos.y < size.x;
}

void Maze::printSignatures()
{
    for(int y = 0; y < size.y; y++)
    {
        for(int x = 0; x < size.x; x++)
        {
            std::cout << (int)grid[y][x].getSignature() << " ";
        }
        std::cout << std::endl;
    }
}