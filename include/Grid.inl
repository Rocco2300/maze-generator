
template <typename T>
Grid<T>::Grid()
{
    data = nullptr;
}

template <typename T>
Grid<T>::Grid(Vector size)
{
    this->size = size;
    data = new T*[size.y];
    for(int i = 0; i < size.y; i++)
    {
        data[i] = new T[size.x];
    }
}

template <typename T>
T* Grid<T>::operator[](int index)
{
    assert(index < size.x && index < size.y);
    return data[index];
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
Grid<T>::~Grid()
{
    for(int i = 0; i < size.y; i++)
    {
        delete[] data[i];
    }
    delete[] data;
}
