
template <typename T>
Grid<T>::Grid()
{
    data = nullptr;
}

template <typename T>
Grid<T>::Grid(Coord size)
{
    this->size = size;
    data = new T[size.x * size.y];
}

template <typename T>
T& Grid<T>::operator()(int x, int y)
{
    assert(x < size.x && y < size.y && x >= 0 && y >= 0);
    return data[y * size.x + x];
}

template <typename T>
T& Grid<T>::operator()(const Coord& c)
{
    assert(c.x < size.x && c.y < size.y && c.x >= 0 && c.y >= 0);
    return data[c.y * size.x + c.x];
}

template <typename T>
Grid<T>& Grid<T>::operator=(const Grid<T>& grid)
{
    if(this == &grid)
        return *this;

    delete[] data;

    this->size = grid.size;
    data = new T[size.x * size.y];

    for(int i = 0; i < size.x * size.y; i++)
    {
        this->data[i] = grid.data[i];
    }
    return *this;
}

template <typename T>
Coord Grid<T>::getSize()
{
    return size;
}

template <typename T>
Grid<T>::~Grid()
{
    delete[] data;
}
