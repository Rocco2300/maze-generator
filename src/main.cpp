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

    // const Coord size(3, 7);
    // Grid<int> grid({size.x, size.y});
    // for(int i = 0; i < size.y; i++)
    // {
    //     for(int j = 0; j < size.x; j++)
    //     {
    //         grid(i, j) = 0;
    //         std::cout << grid(i, j) << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // grid({6, 2}) = 0;

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

    // auto start = steady_clock::now();
    maze.generateMaze();
    // auto end = steady_clock::now();
    // auto duration = duration_cast<microseconds>(end - start);
    // std::cout << "The generation took: " << duration.count() << " μs" << std::endl;
    std::ofstream out("maze.txt");
    maze.output(std::cout, OutputType::Maze);
    out.close();
    return 0;
}