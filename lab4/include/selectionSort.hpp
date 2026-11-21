#ifndef SORT_HPP

#define SORT_HPP
#include <vector>
#include <functional>

/*
template <typename T>
void sort();
*/

template <typename T>
void selectionSort(int, int, T *, std::function<bool(const T &, const T &)>);

#include "../src/selectionSort.cpp"

#endif