#include "MapGenerator.h"
#include <vector>

MapGenerator::MapGenerator() 
{ }

MapGenerator::MapGenerator(Map& map)
{
    this->size = map.getSize();
    this->mapGrid = map.getMapData();
}

void MapGenerator::randomizeStart()
{   
    start.x = rand() % size.x;
    start.y = rand() % size.y;
}

void MapGenerator::generateMap()
{

}

Direction MapGenerator::getRandomDir(Cell* cell)
{
    std::vector<Direction> dirs;
    Cell** cells = cell->getNeighbours();

    for(int i = 0; i < 4; i++)
    {
        if(cells[i] != nullptr)
            dirs.push_back((Direction)i);
    }

    return dirs[rand() % dirs.size()];
}

void MapGenerator::generate(Cell* cell)
{
    cell->setVisited(true);
    cell->removeFromNeighbours();
    
    Direction newDir = getRandomDir(cell);
    
}