#include <iostream>
#include <random>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <fstream>
#include "Maze.h"

using namespace std::chrono;

int main()
{
    srand(time(NULL));


    const Coord size(11, 11);
    Maze maze({size.x, size.y});

    maze.setObstacle({0, 0}, true);
    maze.setObstacle({0, 1}, true);
    maze.setObstacle({0, 4}, true);
    maze.setObstacle({0, 5}, true);
    maze.setObstacle({0, 6}, true);
    maze.setObstacle({0, 9}, true);
    maze.setObstacle({0, 10}, true);
    maze.setObstacle({1, 0}, true);
    maze.setObstacle({1, 5}, true);
    maze.setObstacle({1, 10}, true);

    int cnt = 1;
    for(int y = 4; y < size.y; y++)
    {
        for(int x = 0; x < cnt; x++)
        {
            maze.setObstacle({y, x}, true);
            maze.setObstacle({y, size.x - 1 - x}, true);
        }
        cnt++;
    }

    maze.generateMaze();
    maze.printMaze2();
    return 0;
}