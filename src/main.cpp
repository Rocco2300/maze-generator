#include <iostream>
#include <random>
#include <algorithm>
#include <ctime>
#include "Maze.h"

int main()
{
    srand(time(NULL));
    Maze maze({5, 4});
    maze.printSignatures();
    return 0;
}