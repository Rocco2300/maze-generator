#include <iostream>
#include <random>
#include <algorithm>
#include <ctime>
#include "Maze.h"

int main()
{
    srand(time(NULL));
    // for(int i = 0; i < 16; i++)
    // {
    //     int size = randDirTable[i].size;
    //     for(int j = 0; j < size; j++)
    //     {
    //         std::cout << (int)randDirTable[i].directions[j] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    Maze maze({5, 4});
    maze.printSignatures();
    int signature = maze[0][0].getSignature();
    int size = randDirTable[signature].size;
    for(int i = 0; i < size; i++)
    {
        std::cout << (int)randDirTable[signature].directions[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}