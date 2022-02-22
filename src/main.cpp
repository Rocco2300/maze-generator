#include <iostream>
#include <random>
#include <algorithm>
#include <ctime>
#include "Maze.h"

int main()
{
    srand(time(NULL));
    for(int i = 0; i < 16; i++)
    {
        int size = randDirTable[i].size;
        for(int j = 0; j < size; j++)
        {
            std::cout << (int)randDirTable[i].data[j] << " ";
        }
        std::cout << std::endl;
    }

    // Maze maze({5, 4});
    // maze.printSignatures();
    // for(int i = 0; i < 16; i++)
    // {
    //     for(int j = 0; j < randDirTable[i].size(); j++)
    //     {
    //         std::cout << (int)randDirTable[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }
    return 0;
}