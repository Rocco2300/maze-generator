#include <iostream>
#include <random>
#include <algorithm>
#include <ctime>
#include "Maze.h"

int main()
{
    srand(time(NULL));

    Maze maze({100, 100});
    // maze.generateMaze();
    int cnt = 0;
    for(int i = 0; i < 1000; i++)
    {
        cnt++;
        maze.generateMaze();
        maze.reset();
    }
    std::cout << cnt << std::endl;
    // maze.printSignatures();
    return 0;
}