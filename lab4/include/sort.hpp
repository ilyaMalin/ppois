#ifndef SORT_HPP

#define SORT_HPP
#include <vector>
#include <utility>
#include <functional>

/*
template <typename T>
void selectionSort();
*/

template <typename T>
void selectionSort(int, int, T *, std::function<bool(const T &, const T &)>);

#include "../src/sort.cpp"

#endif