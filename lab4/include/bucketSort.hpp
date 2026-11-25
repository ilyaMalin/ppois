#ifndef BUCKETSORT_HPP

#define BUCKETSORT_HPP
#include <iterator>
#include <functional>
#include <vector>

template <typename iterator, typename bucketIndex, typename condition = std::less<typename std::iterator_traits<iterator>::value_type>>
void bucketSort(iterator, iterator, std::size_t, bucketIndex, condition = condition{});

template <typename T, typename bucketIndex, typename condition = std::less<>>
void bucketSort(std::vector<T> &, std::size_t, bucketIndex, condition = condition{});

#include "../src/bucketSort.cpp"

#endif