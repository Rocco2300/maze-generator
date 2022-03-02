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


    const Coord size(11, 9);
    Maze maze({size.x, size.y});

    maze.setObstacle({0, 0});
    maze.setObstacle({0, 1});
    maze.setObstacle({0, 4});
    maze.setObstacle({0, 5});
    maze.setObstacle({0, 6});
    maze.setObstacle({0, 9});
    maze.setObstacle({0, 10});
    maze.setObstacle({1, 0});
    maze.setObstacle({1, 5});
    maze.setObstacle({1, 10});

    int cnt = 1;
    for(int y = 4; y < size.y; y++)
    {
        for(int x = 0; x < cnt; x++)
        {
            maze.setObstacle({y, x});
            maze.setObstacle({y, size.x - 1 - x});
        }
        cnt++;
    }

    maze.generateMaze();
    maze.printMaze();
    return 0;
}