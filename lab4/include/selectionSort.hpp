#ifndef SELECTIONSORT_HPP

#define SELECTIONSORT_HPP
#include <iterator>
#include <vector>
#include <functional>

template <typename T>
void selectionSort(int, int, T *, std::function<bool(const T &, const T &)> = [](const T &a, const T &b)
                                  { return a < b; });

template <typename iterator, typename condition = std::less<typename std::iterator_traits<iterator>::value_type>>
void selectionSort(iterator, iterator, condition = condition());

template <typename T, typename condition = std::less<>>
void selectionSort(std::vector<T> &, condition = condition());

#include "../src/selectionSort.cpp"

#endif