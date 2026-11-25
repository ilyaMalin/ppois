#include <UnitTest++/UnitTest++.h>
#include "bucketSort.hpp"
#include <stdexcept>

std::size_t intBucket(const int &a) { return a / 10; }
std::size_t floatBucket(const float &a) { return static_cast<std::size_t>(a); }

TEST(BUCKETSORTITERATORFULL)
{
    int arr[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int res[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    bucketSort(arr, arr + 10, 5, intBucket);
    CHECK_ARRAY_EQUAL(arr, res, 10);

    CHECK_THROW(bucketSort(arr, arr + 10, 0, intBucket), std::invalid_argument);
    CHECK_THROW(bucketSort(arr, arr + 10, 1, intBucket), std::out_of_range);

    int revRes[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 10};
    bucketSort(arr, arr + 10, 5, intBucket, std::greater<int>());
    CHECK_ARRAY_EQUAL(arr, revRes, 10);

    CHECK_THROW(bucketSort(arr, arr + 10, 0, intBucket, std::greater<int>()), std::invalid_argument);
    CHECK_THROW(bucketSort(arr, arr + 10, 1, intBucket, std::greater<int>()), std::out_of_range);
}

TEST(BUCKETSORTVECTORFULL)
{
    std::vector<float> vec = {4.5f, 1.2f, 3.8f, 0.1f, 2.9f};
    std::vector<float> res = {0.1f, 1.2f, 2.9f, 3.8f, 4.5f};

    bucketSort(vec, 5, floatBucket);
    CHECK_ARRAY_EQUAL(vec, res, 5);

    CHECK_THROW(bucketSort(vec, 0, floatBucket), std::invalid_argument);
    CHECK_THROW(bucketSort(vec, 2, floatBucket), std::out_of_range);

    std::vector<float> vec2 = {1.2f, 1.8f, 0.5f, 0.9f};
    std::vector<float> revRes = {0.9f, 0.5f, 1.8f, 1.2f};
    bucketSort(vec2, 5, floatBucket, std::greater<float>());
    CHECK_ARRAY_EQUAL(vec2, revRes, 4);

    CHECK_THROW(bucketSort(vec2, 0, floatBucket, std::greater<float>()), std::invalid_argument);
    CHECK_THROW(bucketSort(vec2, 1, floatBucket, std::greater<float>()), std::out_of_range);
}