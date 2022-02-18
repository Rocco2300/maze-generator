#include "Map.h"
#include <iostream>

Map::Map()
{
}

Map::Map(Vector size)
{
    this->size = size;
    grid = Grid(size);

    for(int y = 0; y < size.y; y++)
    {
        for(int x = 0; x < size.x; x++)
        {
            grid[y][x] = Cell({y, x});

            for(int dir = 0; dir < 4; dir++)
            {
                Vector newPos = getPositionFromDir({y, x}, (Direction)dir);

                if(isCellInBounds(newPos))
                    grid[y][x].setNeighbour(dir, &grid[newPos.y][newPos.x]);
            }
        }
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

Vector Map::getPositionFromDir(Vector currentPos, Direction dir)
{
    // Due to the fact the we invert x and y to make traversing 
    // the matrix more logical in cartesian coordinates, we have to
    // invert the result so as res(x, y) = currentPos(y, x)
    Vector res;
    switch(dir)
    {
    case Up:
        res.x = currentPos.y;
        res.y = currentPos.x - 1;
        break;
    case Right:
        res.x = currentPos.y + 1;
        res.y = currentPos.x;
        break;
    case Down:
        res.x = currentPos.y;
        res.y = currentPos.x + 1;
        break;
    case Left:
        res.x = currentPos.y - 1;
        res.y = currentPos.x;
        break;
    }
    return res;
}

bool Map::isCellInBounds(Vector pos)
{
    return pos.x >= 0 && pos.x < size.x && pos.y >= 0 && pos.y < size.y;
}