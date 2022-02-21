#pragma once

#include "Map.h"

class MapGenerator
{
private:
    Vector size;
    Grid<Cell>* mapGrid;
public:
    MapGenerator();
    MapGenerator(Map& map);
    void generateMap();
private:
    Vector randomizeStartPos();
    Direction getRandomDir(Cell* cell);
    void generate(Cell* cell);
};
