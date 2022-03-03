#include "Maze.h"
#if DEBUG
#include <iostream>
#include <iomanip>
#endif

Maze::Maze()
{
}

Maze::Maze(Vec2 size)
{
    this->size = size;
    grid = Grid<Cell>(size);
    maze = Grid<uint8_t>({size.w * 2 + 1, size.h * 2 + 1});

    for(int y = 0; y < size.h; y++)
    {
        for(int x = 0; x < size.w; x++)
        {
            Vec2 currentCoord(x, y);
            grid(currentCoord) = Cell();

            for(int dir = 0; dir < 4; dir++)
            {
                Vec2 nextCoord = currentCoord + dirOffset[dir];
                if(isCellInBounds(nextCoord))
                {
                    grid(currentCoord).addSignature(dirToFlag[dir]);
                }
            }
        }
    }
}

void Maze::reset()
{
    for(int y = 0; y < size.h; y++)
    {
        for(int x = 0; x < size.w; x++)
        {
            Vec2 currentCoord(x, y);

            for(int dir = 0; dir < 4; dir++)
            {
                Vec2 nextCoord = currentCoord + dirOffset[dir];
                if(isCellInBounds(nextCoord))
                {
                    grid(x, y).addSignature(dirToFlag[dir]);
                    grid(x, y).resetWalls();
                }
            }
        }
    }
}

void Maze::removeNeighbourSignatures(Vec2 coord)
{
    for(int dir = 0; dir < 4; dir++)
    {
        Vec2 nextCoord = coord + dirOffset[dir];

        if(isCellInBounds(nextCoord))
        {
            Direction opposite = oppositeDir[dir];
            grid(nextCoord).removeSignature(dirToFlag[(int)opposite]);
        }
    }
}

void Maze::setObstacle(Vec2 coord)
{
    if(coord.x >= size.w || coord.y >= size.h || coord.x < 0 || coord.y < 0)
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
    for(int y = 0; y < size.h * 2 + 1; y++)
    {
        for(int x = 0; x < size.w * 2 + 1; x++)
        {
            maze(x, y) = 0;
        }
    }

    for(int y = 1; y < size.h * 2 + 1; y += 2)
    {
        for(int x = 1; x < size.w * 2 + 1; x += 2)
        {
            auto cell = grid((x-1)/2, (y-1)/2);
            if(cell.isObstacle())
                continue;
            
            if(cell.hasWall(DirFlag::North))
            {
                maze(x-1, y-1) |= static_cast<uint8_t>(DirFlag::West);
                maze(x  , y-1) |= static_cast<uint8_t>(DirFlag::East) | static_cast<uint8_t>(DirFlag::West);
                maze(x+1, y-1) |= static_cast<uint8_t>(DirFlag::East);
            }

            if(cell.hasWall(DirFlag::East))
            {
                maze(x+1, y-1) |= static_cast<uint8_t>(DirFlag::North);
                maze(x+1, y  ) |= static_cast<uint8_t>(DirFlag::North) | static_cast<uint8_t>(DirFlag::South);
                maze(x+1, y+1) |= static_cast<uint8_t>(DirFlag::South);
            }

            if(cell.hasWall(DirFlag::South))
            {
                maze(x-1, y+1) |= static_cast<uint8_t>(DirFlag::West);
                maze(x  , y+1) |= static_cast<uint8_t>(DirFlag::East) | static_cast<uint8_t>(DirFlag::West);
                maze(x+1, y+1) |= static_cast<uint8_t>(DirFlag::East);
            }

            if(cell.hasWall(DirFlag::West))
            {
                maze(x-1, y-1) |= static_cast<uint8_t>(DirFlag::North);
                maze(x-1, y  ) |= static_cast<uint8_t>(DirFlag::North) | static_cast<uint8_t>(DirFlag::South);
                maze(x-1, y+1) |= static_cast<uint8_t>(DirFlag::South);
            }
        }
    }
}

void Maze::generateMaze()
{
    Vec2 start;
    do
    {
        start.x = rand() % size.w;
        start.y = rand() % size.h;
    } while(grid(start).isObstacle());

    generate(start);
    generateMazeGrid();
}

void Maze::generate(Vec2 start)
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
        for(int y = 0; y < size.h * 2 + 1; y++)
        {
            for(int x = 0; x < size.w * 2 + 1; x++)
            {
                switch(maze(x, y))
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
        for(int y = 0; y < size.h; y++)
        {
            for(int x = 0; x < size.w; x++)
            {
                out << std::hex << (int)grid(x, y).isObstacle() << (int)grid(x, y).getWalls() << " ";
            }
            out << "\n";
        }
    }
}

/*
This function loads a maze from the data in the stream.
Warning: make sure the stream contains data not
visual maze output
*/
void Maze::load(std::istream& in)
{
    in >> std::hex >> size.w >> size.h;
   
    grid = Grid<Cell>(size);
    maze = Grid<uint8_t>({size.x * 2 + 1, size.y * 2 + 1});

    for(int y = 0; y < size.h; y++)
    {
        for(int x = 0; x < size.w; x++)
        {
            int data;
            in >> std::hex >> data;
            Cell cell;
            cell.setObstacle(data & 0b10000);
            cell.setWalls(data & 0b1111);
            cell.setSignature(0);
            grid(x, y) = cell;
        }
    }   
    
    generateMazeGrid();
}

bool Maze::isCellInBounds(Vec2 pos)
{
    return pos.x >= 0 && pos.x < size.w && pos.y >= 0 && pos.y < size.h;
}

#if DEBUG
void Maze::printWalls()
{
    for(int y = 0; y < size.h; y++)
    {
        for(int x = 0; x < size.w; x++)
        {
            std::cout << std::setw(2) << (int)grid(x, y).getWalls() << " ";
        }
        std::cout << std::endl;
    }
}

void Maze::printSignatures()
{
    for(int y = 0; y < size.h; y++)
    {
        for(int x = 0; x < size.w; x++)
        {
            std::cout << std::setw(2) << (int)grid(x, y).getSignature() << " ";
        }
        std::cout << std::endl;
    }
}

void Maze::printObstacles()
{
    for(int y = 0; y < size.h; y++)
    {
        for(int x = 0; x < size.w; x++)
        {
            std::cout << grid(x, y).isObstacle() << " ";
        }
        std::cout << std::endl;
    }
}

void Maze::printMazeGrid()
{
    for(int y = 0; y < size.h * 2 + 1; y++)
    {
        for(int x = 0; x < size.w * 2 + 1; x++)
        {
            std::cout << std::setw(2) << (int)maze(x, y) << " ";
        }
        std::cout << std::endl;
    }
}
#endif