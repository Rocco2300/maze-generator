#include <iostream>
#include "Cell.h"

Vector getPositionFromDir(Vector currentPos, int dir)
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

bool isCellInBounds(Vector pos)
{
    return pos.x >= 0 && pos.x < 5 && pos.y >= 0 && pos.y < 5;
}

int main()
{
    Cell grid[5][5];    
    for(int y = 0; y < 5; y++)
    {
        for(int x = 0; x < 5; x++)
        {
            grid[y][x] = Cell({y, x});

            for(int dir = 0; dir < 4; dir++)
            {
                Vector newPos = getPositionFromDir({y, x}, dir);

                if(isCellInBounds(newPos))
                    grid[y][x].setNeighbour(dir, &grid[newPos.y][newPos.x]);
            }
        }
    }
    return 0;
}