#pragma once

#include <iostream>
#include <cassert>
#include <cstdint>

struct Coord
{
    int x, y;

    Coord() { }
    Coord(int _x, int _y) : x{_x}, y{_y} { }

    Coord operator+(const Coord& other)
    {
        Coord res(x + other.x, y + other.y);
        return res;
    }

    friend std::ostream& operator<<(std::ostream& out, const Coord& coord);
};

enum class Direction
{
    North = 0,
    East,
    South,
    West,
};

enum class DirFlag
{
    North = 1,
    East = 1 << 1,
    South = 1 << 2,
    West = 1 << 3
};

class Cell
{
private:
    Coord pos;
    uint8_t signature;
    uint8_t walls;
public:
    Cell();
    Cell(Coord pos);
    Coord getPosition();
    uint8_t getWalls();
    uint8_t getSignature();
    void destroyWall(Direction dir);
    void addSignature(DirFlag dir);
    void removeSignature(DirFlag dir);
};