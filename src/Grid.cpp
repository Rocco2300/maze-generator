#include "Grid.h"

Grid::Grid()
{
}

Grid::Grid(Vector size)
{
    this->size = size;
    data = new Cell*[size.y];
    for(int i = 0; i < size.y; i++)
    {
        data[i] = new Cell[size.x];
    }
}

Cell* Grid::operator[](int index)
{
    return data[index];
}

Grid::~Grid()
{
    for(int i = 0; i < size.y; i++)
    {
        delete[] data[i];
    }
    delete[] data;
}