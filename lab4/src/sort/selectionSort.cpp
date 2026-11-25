#include <algorithm>
#include <functional>
#include <stdexcept>

template <typename T>
void selectionSort(int _start, int _end, T *_array, std::function<bool(const T &, const T &)> _condition)
{
    if (!_array || _start >= _end || _start < 0)
    {
        throw std::range_error("Пустой массив или выход за его пределы!\n");
    }

    for (int i = _start; i < _end; i++)
    {
        int _swappedElement = i;

        for (int j = i + 1; j < _end; j++)
        {
            if (_condition(_array[j], _array[_swappedElement]))
            {
                _swappedElement = j;
            }
        }

        if (_swappedElement != i)
        {
            std::swap(_array[i], _array[_swappedElement]);
        }
    }
}

template <typename iterator, typename condition>
void selectionSort(iterator _start, iterator _end, condition _condition)
{
    if (_start == _end)
    {
        return;
    }

    for (iterator i = _start; i != _end; i++)
    {
        iterator _swappedElement = i;

        for (iterator j = i + 1; j != _end; ++j)
        {
            if (_condition(*j, *_swappedElement))
            {
                _swappedElement = j;
            }
        }

        if (_swappedElement != i)
        {
            std::iter_swap(i, _swappedElement);
        }
    }
}

template <typename T, typename condition>
void selectionSort(std::vector<T> &_vector, condition _condition)
{
    selectionSort(_vector.begin(), _vector.end(), _condition);
}