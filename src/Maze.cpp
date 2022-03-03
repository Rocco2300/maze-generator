#include "Maze.h"
#if DEBUG
#include <iostream>
#include <iomanip>
#endif

Maze::Maze()
{
}

Maze::Maze(Coord size)
{
    this->size = size;
    grid = Grid<Cell>(size);
    maze = Grid<uint8_t>({size.x * 2 + 1, size.y * 2 + 1});

    for(int y = 0; y < size.y; y++)
    {
        for(int x = 0; x < size.x; x++)
        {
            Coord currentCoord(y, x);
            grid(currentCoord) = Cell(currentCoord);

            for(int dir = 0; dir < 4; dir++)
            {
                Coord nextCoord = currentCoord + dirOffset[dir];
                if(isCellInBounds(nextCoord))
                {
                    grid(currentCoord).addSignature(dirToFlag[dir]);
                }
            }
        }
    }

    for(int y = 0; y < size.y * 2 + 1; y++)
    {
        for(int x = 0; x < size.x * 2 + 1; x++)
        {
            maze(y, x) = 0;
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
                    grid(y, x).addSignature(dirToFlag[dir]);
                    grid(y, x).resetWalls();
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
            grid(nextCoord).removeSignature(dirToFlag[(int)opposite]);
        }
    }
}

void Maze::setObstacle(Coord coord)
{
    if(coord.x >= size.y || coord.y >= size.x || coord.x < 0 || coord.y < 0)
    {
        std::cerr << "Cell that you are trying to make obstacle is out of bounds!\n";
        return;
    }
    grid(coord).setObstacle(true);
    grid(coord).setSignature(0);
    removeNeighbourSignatures(coord);
}

void Maze::generateMazeGrid()
{
    for(int y = 1; y < size.y * 2 + 1; y += 2)
    {
        for(int x = 1; x < size.x * 2 + 1; x += 2)
        {
            auto cell = grid((y-1)/2, (x-1)/2);
            if(cell.isObstacle())
                continue;
            
            if(cell.hasWall(DirFlag::North))
            {
                maze(y-1, x-1) |= static_cast<uint8_t>(DirFlag::West);
                maze(y-1, x  ) |= static_cast<uint8_t>(DirFlag::East) | static_cast<uint8_t>(DirFlag::West);
                maze(y-1, x+1) |= static_cast<uint8_t>(DirFlag::East);
            }

            if(cell.hasWall(DirFlag::East))
            {
                maze(y-1, x+1) |= static_cast<uint8_t>(DirFlag::North);
                maze(y  , x+1) |= static_cast<uint8_t>(DirFlag::North) | static_cast<uint8_t>(DirFlag::South);
                maze(y+1, x+1) |= static_cast<uint8_t>(DirFlag::South);
            }

            if(cell.hasWall(DirFlag::South))
            {
                maze(y+1, x-1) |= static_cast<uint8_t>(DirFlag::West);
                maze(y+1, x  ) |= static_cast<uint8_t>(DirFlag::East) | static_cast<uint8_t>(DirFlag::West);
                maze(y+1, x+1) |= static_cast<uint8_t>(DirFlag::East);
            }

            if(cell.hasWall(DirFlag::West))
            {
                maze(y-1, x-1) |= static_cast<uint8_t>(DirFlag::North);
                maze(y  , x-1) |= static_cast<uint8_t>(DirFlag::North) | static_cast<uint8_t>(DirFlag::South);
                maze(y+1, x-1) |= static_cast<uint8_t>(DirFlag::South);
            }
        }
    }
}

void Maze::generateMaze()
{
    Coord start;
    do
    {
        start.x = rand() % size.y;
        start.y = rand() % size.x;
    } while(grid(start).isObstacle());

    generate(start);
    generateMazeGrid();
}

void Maze::generate(Coord start)
{
    stack.push(start);

    while(!stack.empty())
    {
        auto coord = stack.top();
        removeNeighbourSignatures(coord);
        
        if(grid(coord).getSignature() != 0)
        {
            auto sign = grid(coord).getSignature();
            auto randIndex = rand() % randDirTableSizes[sign];
            auto nextDir = randDirTable[sign][randIndex];
            auto offset = coord + dirOffset[(int)nextDir];

            grid(coord).destroyWall(dirToFlag[(int)nextDir]);
            grid(offset).destroyWall(dirToFlag[(int)oppositeDir[(int)nextDir]]);

            grid(coord).removeSignature(dirToFlag[(int)nextDir]);
            stack.push(offset);
        }
        else
        {
            stack.pop();
        }
    }
}

void Maze::output(std::ostream& out, OutputType type)
{
    if(type == OutputType::Maze)
    {
        for(int y = 0; y < size.y * 2 + 1; y++)
        {
            for(int x = 0; x < size.x * 2 + 1; x++)
            {
                switch(maze(y, x))
                {
                case 0b0000: out << reinterpret_cast<const char*>(u8"  ");           break;
                case 0b0001: out << reinterpret_cast<const char*>(u8"\u2577 ");      break;
                case 0b0010: out << reinterpret_cast<const char*>(u8"\u2574 ");      break;
                case 0b0011: out << reinterpret_cast<const char*>(u8"\u2510 ");      break;    
                case 0b0100: out << reinterpret_cast<const char*>(u8"\u2575 ");      break;
                case 0b0101: out << reinterpret_cast<const char*>(u8"\u2502 ");      break;
                case 0b0110: out << reinterpret_cast<const char*>(u8"\u2518 ");      break;
                case 0b0111: out << reinterpret_cast<const char*>(u8"\u2524 ");      break;
                case 0b1000: out << reinterpret_cast<const char*>(u8" \u2576");      break;
                case 0b1001: out << reinterpret_cast<const char*>(u8"\u250C\u2500"); break;
                case 0b1010: out << reinterpret_cast<const char*>(u8"\u2500\u2500"); break;
                case 0b1011: out << reinterpret_cast<const char*>(u8"\u252C\u2500"); break;
                case 0b1100: out << reinterpret_cast<const char*>(u8"\u2514\u2500"); break;
                case 0b1101: out << reinterpret_cast<const char*>(u8"\u251C\u2500"); break;
                case 0b1110: out << reinterpret_cast<const char*>(u8"\u2534\u2500"); break;
                case 0b1111: out << reinterpret_cast<const char*>(u8"\u253C\u2500"); break;
                }
            }
            out << "\n";
        }
    }
    else if(type == OutputType::Data)
    {
        out << std::hex << size.x << " " << size.y << "\n";
        for(int y = 0; y < size.y; y++)
        {
            for(int x = 0; x < size.x; x++)
            {
                out << std::hex << (int)grid(y, x).isObstacle() << (int)grid(y, x).getWalls() << " ";
            }
            out << "\n";
        }
    }
}

bool Maze::isCellInBounds(Coord pos)
{
    return pos.x >= 0 && pos.x < size.y && pos.y >= 0 && pos.y < size.x;
}

#if DEBUG
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
            std::cout << std::setw(2) << (int)grid[y][x].getWalls() << " ";
        }
        std::cout << std::endl;
    }
}

void Maze::printSignatures()
{
    for(int y = 0; y < size.y; y++)
    {
        for(int x = 0; x < size.x; x++)
        {
            std::cout << std::setw(2) << (int)grid[y][x].getSignature() << " ";
        }
        std::cout << std::endl;
    }
}

void Maze::printObstacles()
{
    for(int y = 0; y < size.y; y++)
    {
        for(int x = 0; x < size.x; x++)
        {
            std::cout << grid[y][x].isObstacle() << " ";
        }
        std::cout << std::endl;
    }
}

void Maze::printMazeGrid()
{
    for(int y = 0; y < size.y * 2 + 1; y++)
    {
        for(int x = 0; x < size.x * 2 + 1; x++)
        {
            std::cout << std::setw(2) << (int)maze[y][x] << " ";
        }
        std::cout << std::endl;
    }
}
#endif