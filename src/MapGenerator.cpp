#include "MapGenerator.h"
#include <iostream>
#include <vector>

MapGenerator::MapGenerator() 
{ }

MapGenerator::MapGenerator(Map& map)
{
    this->size = map.getSize();
    this->mapGrid = map.getMapData();
}

Vector MapGenerator::randomizeStartPos()
{   
    Vector start;
    start.x = rand() % size.x;
    start.y = rand() % size.y;
    return start;
}

void MapGenerator::generateMap()
{
    auto start = randomizeStartPos();
    generate(&mapGrid->at(start.x, start.y));
}

Direction MapGenerator::getRandomDir(Cell* cell)
{
    std::vector<Direction> dirs;
    auto cells = cell->getNeighbours();

    for(int i = 0; i < 4; i++)
    {
        if(cells[i] != nullptr)
            dirs.push_back((Direction)i);
    }

    return dirs[rand() % dirs.size()];
}

Direction getOpposite(Direction dir)
{
    int temp = ((int)dir + 2) % 4;
    return (Direction)temp;
}

void MapGenerator::generate(Cell* cell)
{
    cell->setVisited(true);
    cell->removeFromNeighbours();
    
    while(cell->getNumberOfNeighbours())
    {
        auto newDir = getRandomDir(cell);
        auto newPos = cell->getPositionFromDir(newDir);
        auto newCell = mapGrid->at(newPos.x, newPos.y);

        cell->destroyWall(newDir);
        newCell.destroyWall(getOpposite(newDir));

        generate(&newCell);
    }
}