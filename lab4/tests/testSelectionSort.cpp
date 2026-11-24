#include <UnitTest++/UnitTest++.h>
#include "selectionSort.hpp"
#include <stdexcept>
#include <deque>

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

TEST(EMPTYVECTOR)
{
    std::vector<int> vec = {};
    std::vector<int> result = {};

    selectionSort(vec);
    CHECK_ARRAY_EQUAL(vec, result, result.size());
}

TEST(VECTOR)
{
    std::vector<int> vec = {5, 12, -8, 14, 1, -4};
    std::vector<int> result = {-8, -4, 1, 5, 12, 14};

    selectionSort(vec);
    CHECK_ARRAY_EQUAL(vec, result, result.size());
}

TEST(NOCHANGEVECTOR)
{
    std::vector<int> vec = {1, 2, 3, 4, 5, 6};
    std::vector<int> result = {1, 2, 3, 4, 5, 6};

    selectionSort(vec);
    CHECK_ARRAY_EQUAL(vec, result, result.size());
}

TEST(REVERSEVECTOR)
{
    auto cmp = [](int a, int b)
    {
        return a > b;
    };

    std::vector<int> empty;
    selectionSort(empty, cmp);
    CHECK(empty.empty());

    std::vector<int> vec = {5, 12, -8, 14, 1, -4};
    std::vector<int> result = {14, 12, 5, 1, -4, -8};

    selectionSort(vec, cmp);

    CHECK_ARRAY_EQUAL(vec, result, result.size());
}

TEST(EMPTYDEQUE)
{
    std::deque<int> deque;

    selectionSort(deque.begin(), deque.end());
    CHECK(deque.empty());
}

TEST(DEQUE)
{
    std::deque<int> deque;
    deque.push_back(5);
    deque.push_back(-2);
    deque.push_back(7);
    deque.push_back(12);
    deque.push_back(-10);

    selectionSort(deque.begin(), deque.end());

    std::vector<int> vec;
    auto it = deque.begin();
    while (it != deque.end())
    {
        vec.push_back(*it);
        it++;
    }

    std::vector<int> result = {-10, -2, 5, 7, 12};

    CHECK_ARRAY_EQUAL(vec, result, result.size());
}

TEST(NOCHANGEDEQUE)
{
    std::deque<int> deque;
    deque.push_back(1);
    deque.push_back(2);
    deque.push_back(3);
    deque.push_back(4);
    deque.push_back(5);

    selectionSort(deque.begin(), deque.end());

    std::vector<int> vec;
    auto it = deque.begin();
    while (it != deque.end())
    {
        vec.push_back(*it);
        it++;
    }

    std::vector<int> result = {1, 2, 3, 4, 5};

    CHECK_ARRAY_EQUAL(vec, result, result.size());
}

TEST(REVERSEDEQUE)
{
    auto cmp = [](int a, int b)
    {
        return a > b;
    };

    std::deque<int> empty;
    selectionSort(empty.begin(), empty.end(), cmp);
    CHECK(empty.empty());

    std::deque<int> deque = {5, -2, 7, 12, -10};

    selectionSort(deque.begin(), deque.end(), cmp);

    std::vector<int> result = {12, 7, 5, -2, -10};
    std::vector<int> vec(deque.begin(), deque.end());

    CHECK_ARRAY_EQUAL(vec, result, result.size());
}