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
    const Vec2 size(9, 9);
    Maze maze({size.x, size.y});

    maze.setObstacle({0, 0});
    maze.setObstacle({1, 0});
    maze.setObstacle({4, 0});
    maze.setObstacle({5, 0});
    maze.setObstacle({6, 0});
    maze.setObstacle({9, 0});
    maze.setObstacle({10, 0}); 
    maze.setObstacle({0, 1});
    maze.setObstacle({5, 1});
    maze.setObstacle({10, 1});

    int cnt = 1;
    for(int y = 4; y < size.y; y++)
    {
        for(int x = 0; x < cnt; x++)
        {
            maze.setObstacle({x, y});
            maze.setObstacle({size.x - 1 - x, y});
        }
        cnt++;
    }

    auto start = steady_clock::now();
    maze.generateMaze();
    auto end = steady_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    std::cout << "The generation took: " << duration.count() << " μs" << std::endl;
    maze.output(std::cout, OutputType::Maze);
    return 0;
}