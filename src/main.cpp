#include <iostream>
#include "Map.h"


int main()
{
    Map map({5, 7});
    map[0][1].destroyWall(Direction::E);
    map.printWalls();
    return 0;
}