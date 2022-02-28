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

    const Coord size(10, 10);
    Maze maze({size.x, size.y});

    auto start = high_resolution_clock::now();
    maze.generateMaze();
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    std::cout << "Generation of the " << size.x << "x" << size.y << " maze took: " << duration.count() << " microseconds." << std::endl;
    maze.printWalls();
    maze.printMaze();
    return 0;
}