#include "selectionSort.hpp"
#include <iostream>
#include <vector>

constexpr int MAXSIZE = 6;

int main()
{

    std::vector<int> vec = {4, 51, 512, 65, 1, 5, 5};

    selectionSort(vec, [](int a, int b)
                  { return a > b; });

    for (auto it = vec.begin(); it != vec.end(); it++)
    {
        std::cout << *it << " ";
    }

    std::cout << std::endl;

    /*
    char arr[MAXSIZE] = {'g', 'a', 'c', 'e', 'f', 'd'};

    std::function<bool(const char &, const char &)> cmp = [](char a, char b)
    {
        return a < b;
    };

    selectionSort(0, 6, arr);

    for (int i = 0; i < MAXSIZE; i++)
    {
        std::cout << arr[i] << " ";
    }

    std::cout << std::endl;*/

    /*
    std::function<bool(const char &, const char &)> cmp1 = [](char a, char b)
    {
        return a > b;
    };
    selectionSort(arr, arr + 6, cmp1);

    for (int i = 0; i < MAXSIZE; i++)
    {
        std::cout << arr[i] << " ";
    }
        */

    return 0;
}