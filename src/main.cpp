#include <iostream>
#include "Map.h"

int main()
{
    Map map({40, 40});
    map.printVisitedMap();
    // Grid<int> grid({10, 5});

    // for(int i = 0; i < 5; i++)
    // {
    //     for(int j = 0; j < 10; j++)
    //     {
    //         grid[i][j] = 0;
    //     }
    // }
    // for(int i = 0; i < 5; i++)
    // {
    //     for(int j = 0; j < 10; j++)
    //     {
    //         std::cout << grid[i][j] << " " ;
    //     }
    //     std::cout << std::endl;
    // }
    return 0;
}