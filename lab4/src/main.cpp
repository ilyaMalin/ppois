#include "selectionSort.hpp"
#include <iostream>

constexpr int MAXSIZE = 6;

int main()
{
    char arr[MAXSIZE] = {'g', 'a', 'c', 'e', 'f', 'd'};

    std::function<bool(const char &, const char &)> cmp = [](char a, char b)
    {
        return a < b;
    };
    selectionSort(0, 6, arr, cmp);

    for (int i = 0; i < MAXSIZE; i++)
    {
        std::cout << arr[i] << " ";
    }

    std::cout << std::endl;

    std::function<bool(const char &, const char &)> cmp1 = [](char a, char b)
    {
        return a > b;
    };
    selectionSort(0, 6, arr, cmp1);

    for (int i = 0; i < MAXSIZE; i++)
    {
        std::cout << arr[i] << " ";
    }

    std::function<bool(const char &, const char &)> cmp2 = [](char a, char b)
    {
        return a < b;
    };
    selectionSort(2, 5, arr, cmp2);

    std::cout << std::endl;

    for (int i = 0; i < MAXSIZE; i++)
    {
        std::cout << arr[i] << " ";
    }

    return 0;
}