#include "Map.h"
#include <iostream>

Map::Map()
{
}

Map::Map(Vector size)
{
    this->size = size;
    grid = Grid<Cell>(size);

    for(int y = 0; y < size.y; y++)
    {
        for(int x = 0; x < size.x; x++)
        {
            grid[y][x] = Cell({y, x});

            for(int dir = 0; dir < 4; dir++)
            {
                Vector newPos = grid[y][x].getPositionFromDir((Direction)dir);

                if(isCellInBounds(newPos))
                {
                    grid[y][x].setNeighbour(dir, &grid[newPos.y][newPos.x]);
                }
            }
        }
    }
}

Vector Map::getSize()
{
    return size;
}

Grid<Cell>* Map::getMapData()
{
    return &grid;
}

Cell* Map::operator[](int index)
{
    return grid[index];
}

void Map::printWalls()
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

void Map::printVisitedMap()
{
    for(int y = 0; y < size.y; y++)
    {
        for(int x = 0; x < size.x; x++)
        {
            std::cout << grid[y][x].isVisited() << " ";
        }
        std::cout << std::endl;
    }
}

void Map::printNeighbours(Vector pos)
{
    grid[pos.x][pos.y].printNeighbours();
}

bool Map::isCellInBounds(Vector pos)
{
    return pos.x >= 0 && pos.x < size.x && pos.y >= 0 && pos.y < size.y;
}