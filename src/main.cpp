#include <iostream>
#include "Map.h"


int main()
{
    Map map({5, 7});
    map.printVisitedMap();
    map.printNeighbours({6, 0});
    return 0;
}