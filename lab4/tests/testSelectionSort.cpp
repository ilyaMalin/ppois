#include <UnitTest++/UnitTest++.h>
#include "selectionSort.hpp"
#include <stdexcept>

TEST(EMPTYARRAY)
{
    std::function<bool(const int &, const int &)> cmp = [](const int &a, const int &b)
    { return a > b; };

    int *arr = nullptr;

    CHECK_THROW(selectionSort(0, 10, arr, cmp), std::range_error);
}

TEST(STARTAFTEREND)
{
    std::function<bool(const int &, const int &)> cmp = [](const int &a, const int &b)
    { return a > b; };

    int arr[] = {3, 4, 51, 61, 77};

    CHECK_THROW(selectionSort(100, 4, arr, cmp), std::range_error);
}

TEST(STARTBEFOREZERO)
{
    std::function<bool(const int &, const int &)> cmp = [](const int &a, const int &b)
    { return a > b; };

    int arr[] = {3, 4, 51, 61, 77};

    CHECK_THROW(selectionSort(-100, 4, arr, cmp), std::range_error);
}

TEST(REVERSE)
{
    std::function<bool(const int &, const int &)> cmp = [](const int &a, const int &b)
    { return a > b; };

    int arr[] = {3, 4, 51, 61, 77};
    int arr1[] = {77, 61, 51, 4, 3};

    selectionSort(0, 5, arr, cmp);

    CHECK_ARRAY_EQUAL(arr1, arr, 5);
}

TEST(NOCHANGE)
{
    std::function<bool(const int &, const int &)> cmp = [](const int &a, const int &b)
    { return a < b; };

    int arr[] = {3, 4, 51, 61, 77};
    int arr1[] = {3, 4, 51, 61, 77};

    selectionSort(0, 5, arr, cmp);

    CHECK_ARRAY_EQUAL(arr1, arr, 5);
}

TEST(CHANGEINRANGE)
{
    std::function<bool(const int &, const int &)> cmp = [](const int &a, const int &b)
    { return a > b; };

    int arr[] = {3, 4, 51, 61, 77};
    int arr1[] = {3, 61, 51, 4, 77};

    selectionSort(1, 4, arr, cmp);

    CHECK_ARRAY_EQUAL(arr1, arr, 5);
}

TEST(NOCHANGEDEFAULT)
{
    int arr[] = {3, 4, 51, 61, 77};
    int arr1[] = {3, 4, 51, 61, 77};

    selectionSort(0, 5, arr);

    CHECK_ARRAY_EQUAL(arr1, arr, 5);
}