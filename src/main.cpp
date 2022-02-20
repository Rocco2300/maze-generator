#include <iostream>
#include <random>
#include <ctime>
#include "Map.h"

int main()
{
    srand(time(NULL));
    Map map({10, 7});
    // map.printVisitedMap();
    return 0;
}