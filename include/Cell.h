#pragma once

#include <iostream>
#include <cassert>
#include <cstdint>

struct Vec2
{
    union 
    {
        struct { int x, y; };
        struct { int w, h; };
    };

    Vec2() { }
    Vec2(int _x, int _y) : x{_x}, y{_y} { }

    Vec2 operator+(const Vec2& other)
    {
        Vec2 res(x + other.x, y + other.y);
        return res;
    }

    friend std::ostream& operator<<(std::ostream& out, const Vec2& coord);
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
    uint8_t signature;
    uint8_t walls;
    bool obstacle;
public:
    Cell();
    void resetWalls();
    void destroyWall(DirFlag dir);
    void addSignature(DirFlag dir);
    void removeSignature(DirFlag dir);
    void setSignature(uint8_t signature);
    void setWalls(uint8_t walls);
    void setObstacle(bool value);
    
    bool hasWall(DirFlag dir);
    uint8_t getWalls();
    uint8_t getSignature();
    bool isObstacle();
};