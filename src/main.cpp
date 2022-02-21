#include <iostream>
#include <random>
#include <algorithm>
#include <ctime>
#include "MapGenerator.h"

int main()
{
    srand(time(NULL));
    Map map({10, 7});
    // MapGenerator gen(map);
    // gen.generateMap();
    map.printVisitedMap();
    return 0;
}