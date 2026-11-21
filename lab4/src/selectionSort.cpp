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

    for (int i = _start; i <= _end; i++)
    {
        int _swappedElement = i;

        for (int j = i + 1; j < _end; j++)
        {
            try
            {
                if (_condition(_array[j], _array[_swappedElement]))
                {
                    _swappedElement = j;
                }
            }
            catch (const std::exception &rangeExcp)
            {
                throw std::range_error("Выход за его пределы!\n");
            }
        }

        if (_swappedElement != i)
        {
            std::swap(_array[i], _array[_swappedElement]);
        }
    }
}