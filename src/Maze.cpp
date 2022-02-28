#include "Maze.h"
#include <iostream>

Maze::Maze()
{
}

Maze::Maze(Coord size)
{
    this->size = size;
    grid = Grid<Cell>(size);
    maze = Grid<char>({size.x * 2 + 1, size.y * 2 + 1});

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
                    grid[y][x].addSignature(dirToFlag[dir]);
                }
            }
        }
    }

    for(int y = 0; y < size.y * 2 + 1; y++)
    {
        for(int x = 0; x < size.y * 2 + 1; x++)
        {
            maze[y][x] = ' ';
        }
    }
}

void Maze::reset()
{
    for(int y = 0; y < size.y; y++)
    {
        for(int x = 0; x < size.x; x++)
        {
            Coord currentCoord(y, x);

            for(int dir = 0; dir < 4; dir++)
            {
                Coord nextCoord = currentCoord + dirOffset[dir];
                if(isCellInBounds(nextCoord))
                {
                    grid[y][x].addSignature(dirToFlag[dir]);
                    grid[y][x].resetWalls();
                }
            }
        }
    }
}

void Maze::removeNeighbourSignatures(Coord coord)
{
    for(int dir = 0; dir < 4; dir++)
    {
        Coord nextCoord = coord + dirOffset[dir];

        if(isCellInBounds(nextCoord))
        {
            Direction opposite = oppositeDir[dir];
            grid[nextCoord.x][nextCoord.y].removeSignature(dirToFlag[(int)opposite]);
        }
    }
}

void Maze::generateViewableMaze()
{
    for(int y = 1; y < size.y * 2 + 1; y += 2)
    {
        for(int x = 1; x < size.x * 2 + 1; x += 2)
        {
            auto cell = grid[(y-1)/2][(x-1)/2];

            for(int corner = 0; corner < 4; corner++)
            {
                auto offset = cornerDirOffset[corner];
                maze[y + offset.y][x + offset.x] = '+';
            }
            
            for(int dir = 0; dir < 4; dir++)
            {
                auto offset = dirOffset[dir];
                auto dirFlag = dirToFlag[dir];

                if(cell.hasWall(dirFlag))
                {
                    if(dir % 2 != 0)
                        maze[y + offset.x][x + offset.y] = '|';
                    else
                        maze[y + offset.x][x + offset.y] = (char)196;
                }
            }
            maze[y][x] = ' ';
        }
    }
}

void Maze::generateMaze()
{
    Coord start;
    start.x = rand() % size.y;
    start.y = rand() % size.x;

    generate2(start);
    generateViewableMaze();
}

void Maze::generate(Coord coord)
{
    // Set as visited for the neighbours
    removeNeighbourSignatures(coord);

    while(grid[coord.x][coord.y].getSignature() != 0)
    {
        auto sign = grid[coord.x][coord.y].getSignature();
        auto randIndex = rand() % randDirTableSizes[sign];
        auto nextDir = randDirTable[sign][randIndex];
        auto offset = coord + dirOffset[(int)nextDir];

        grid[coord.x][coord.y].destroyWall(dirToFlag[(int)nextDir]);
        grid[offset.x][offset.y].destroyWall(dirToFlag[(int)oppositeDir[(int)nextDir]]);

        grid[coord.x][coord.y].removeSignature(dirToFlag[(int)nextDir]);

        generate(offset);
    }
}

void Maze::generate2(Coord start)
{
    stack.push(start);

    while(!stack.empty())
    {
        auto coord = stack.top();
        removeNeighbourSignatures(coord);
        
        if(grid[coord.x][coord.y].getSignature() != 0)
        {
            auto sign = grid[coord.x][coord.y].getSignature();
            auto randIndex = rand() % randDirTableSizes[sign];
            auto nextDir = randDirTable[sign][randIndex];
            auto offset = coord + dirOffset[(int)nextDir];

            grid[coord.x][coord.y].destroyWall(dirToFlag[(int)nextDir]);
            grid[offset.x][offset.y].destroyWall(dirToFlag[(int)oppositeDir[(int)nextDir]]);

            grid[coord.x][coord.y].removeSignature(dirToFlag[(int)nextDir]);
            stack.push(offset);
        }
        else
        {
            stack.pop();
        }
    }
}

void Maze::printMaze()
{
    for(int y = 0; y < size.y * 2 + 1; y ++)
    {
        for(int x = 0; x < size.x * 2 + 1; x ++)
        {
            if(x % 2 != 0)
                std::cout << " " << maze[y][x] << " ";
            else 
                std::cout << maze[y][x];
        }
        std::cout << std::endl;
    }
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