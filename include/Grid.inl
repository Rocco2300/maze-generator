
template <typename T>
Grid<T>::Grid()
{
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
Grid<T>::~Grid()
{
    for(int i = 0; i < size.y; i++)
    {
        delete[] data[i];
    }
    delete[] data;
}
