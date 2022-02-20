#pragma once

#include "Map.h"

class MapGenerator
{
private:
    Vector size;
    Vector start;
    Grid<Cell>* mapGrid;
public:
    MapGenerator();
    MapGenerator(Map& map);
    void randomizeStart();
    void generateMap();
private:
    Direction getRandomDir(Cell* cell);
    void generate(Cell* cell);
};
