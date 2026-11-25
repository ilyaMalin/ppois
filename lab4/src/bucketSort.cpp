#include <algorithm>
#include <functional>
#include <stdexcept>

template <typename iterator, typename bucketIndex, typename condition>
void bucketSort(iterator _start, iterator _end, std::size_t _amountBucket, bucketIndex _bucketIndex, condition _condition)
{
    using valueType = typename std::iterator_traits<iterator>::value_type;

    if (_amountBucket == 0)
    {
        throw std::invalid_argument("Число корзин не может быть 0");
    }

    std::vector<std::vector<valueType>> _buckets(_amountBucket);

    for (iterator i = _start; i != _end; ++i)
    {
        std::size_t _index = _bucketIndex(*i);

        if (_index >= _amountBucket)
        {
            throw std::out_of_range("Выход за предеды вектора");
        }

        _buckets[_index].push_back(*i);
    }

    for (auto &_bucket : _buckets)
    {
        std::stable_sort(
            _bucket.begin(),
            _bucket.end(),
            _condition);
    }

    for (const auto &_bucket : _buckets)
    {
        for (const auto &_element : _bucket)
        {
            *_start = _element;
            ++_start;
        }
    }
}

template <typename T, typename bucketIndex, typename condition>
void bucketSort(std::vector<T> &_arr, std::size_t _amountBucket, bucketIndex _bucketIndex, condition _condition)
{
    bucketSort(_arr.begin(), _arr.end(), _amountBucket, _bucketIndex, _condition);
}