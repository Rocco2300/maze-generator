
template <typename T>
Grid<T>::Grid()
{
    data = nullptr;
}

template <typename T>
Grid<T>::Grid(Coord size)
{
    this->size = size;
    data = new T*[size.y];
    for(int i = 0; i < size.y; i++)
    {
        data[i] = new T[size.x];
    }
}

template <typename T>
Grid<T>::Grid(const Grid& grid)
{
    this->size = grid.size;
    data = new T*[size.y];
    for(int i = 0; i < size.y; i++)
    {
        data[i] = new T[size.x];
    }

    for(int i = 0; i < size.y; i++)
    {
        for(int j = 0; j < size.x; j++)
        {
            this->data[i][j] = grid.data[i][j];
        }
    }
}

template <typename T>
T& Grid<T>::operator()(int x, int y)
{
    assert(x < size.y && y < size.x && x >= 0 && y >= 0);
    return data[x][y];
}

template <typename T>
T& Grid<T>::operator()(const Coord& p)
{
    assert(p.x < size.y && p.y < size.x && p.x >= 0 && p.y >= 0);
    return data[p.x][p.y];
}

template <typename T>
Grid<T>& Grid<T>::operator=(const Grid<T>& grid)
{
    if(this == &grid)
        return *this;

    for(int i = 0; i < size.y; i++)
    {
        delete[] data[i];
    }
    delete[] data;

    this->size = grid.size;
    data = new T*[size.y];
    for(int i = 0; i < size.y; i++)
    {
        data[i] = new T[size.x];
    }

    for(int i = 0; i < size.y; i++)
    {
        for(int j = 0; j < size.x; j++)
        {
            this->data[i][j] = grid.data[i][j];
        }
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
    for(int i = 0; i < size.y; i++)
    {
        delete[] data[i];
    }
    delete[] data;
}
