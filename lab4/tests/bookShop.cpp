#include <UnitTest++/UnitTest++.h>
#include "bookShop.hpp"
#include "selectionSort.hpp"

using expectedBook = std::pair<std::string, float>;

template <typename Shop>
bool checkBookOrder(Shop &shop, const std::vector<expectedBook> &expected)
{
    auto it = shop.begin();

    for (const auto &[name, cost] : expected)
    {
        if (it == shop.end())
            return false;

        if (it->_name != name || it->_cost != cost)
            return false;

        ++it;
    }

    return it == shop.end();
}

TEST(INITBOOKSHOP)
{
    bookShop bookShop(10);

    CHECK(10 == bookShop.getMaxAmount());
}

TEST(SETNEWBOOK)
{
    bookShop bookShop(1);

    std::string _name = "First";
    float _cost = 21.f;
    bookShop.setBook(_name, _cost);

    CHECK(_name == bookShop.getName(_cost));
    CHECK(_cost == bookShop.getCost(_name));

    std::string _name1 = "Second";
    float _cost1 = 23.f;
    bookShop.setBook(_name1, _cost1);

    CHECK(_name1 != bookShop.getName(_cost1));
    CHECK(_cost1 != bookShop.getCost(_name1));

    CHECK(_name == bookShop.getName(_cost));
    CHECK(_cost == bookShop.getCost(_name));
}

TEST(GETBOOK)
{
    bookShop shop(5);

    for (int i = 0; i < 5; i++)
    {
        std::string name = "First" + std::to_string(i);
        float cost = 21.f + i;

        shop.setBook(name, cost);
    }

    for (int i = 0; i < 5; i++)
    {
        std::string name = "First" + std::to_string(i);
        float cost = 21.f + i;

        CHECK(name == shop.getName(cost));
        CHECK(cost == shop.getCost(name));
    }
}

TEST(GETAMOUNBOOK)
{
    bookShop bookShop(5);

    CHECK(5 == bookShop.getMaxAmount());
    CHECK(1 != bookShop.getMaxAmount());
    CHECK(10 != bookShop.getMaxAmount());
}

TEST(EQUALBOOKSHOP)
{
    bookShop first(3);
    bookShop second(3);

    first.setBook("C++", 30.f);
    first.setBook("Python", 20.f);
    first.setBook("Java", 10.f);

    second.setBook("Java", 10.f);
    second.setBook("C++", 30.f);
    second.setBook("Python", 20.f);

    CHECK(first == second);
}

TEST(NOTEQUALBOOKSHOPAMOUNT)
{
    bookShop first(2);
    bookShop second(3);

    first.setBook("C++", 30.f);
    first.setBook("Python", 20.f);

    second.setBook("C++", 30.f);
    second.setBook("Python", 20.f);
    second.setBook("Java", 10.f);

    CHECK(!(first == second));
}

TEST(NOTEQUALBOOKSHOPDATA)
{
    bookShop first(2);
    bookShop second(2);

    first.setBook("C++", 30.f);
    first.setBook("Python", 20.f);

    second.setBook("C++", 30.f);
    second.setBook("Python", 25.f);

    CHECK(!(first == second));
}

TEST(NOTEQUALBOOKSHOPNAME)
{
    bookShop first(2);
    bookShop second(2);

    first.setBook("C++", 30.f);
    first.setBook("Python", 20.f);

    second.setBook("C++", 30.f);
    second.setBook("Java", 20.f);

    CHECK(!(first == second));
}

TEST(SORTBYNAME)
{
    bookShop shop(3);

    shop.setBook("zeta", 10.f);
    shop.setBook("alpha", 30.f);
    shop.setBook("mu", 20.f);

    selectionSort(shop.begin(), shop.end(),
                  [](const auto &a, const auto &b)
                  {
                      return a._name < b._name;
                  });

    std::vector<expectedBook> result = {
        {"alpha", 30.f},
        {"mu", 20.f},
        {"zeta", 10.f}};

    CHECK(checkBookOrder(shop, result));
}

TEST(REVERSESORTBYNAME)
{
    bookShop shop(3);

    shop.setBook("zeta", 10.f);
    shop.setBook("alpha", 30.f);
    shop.setBook("mu", 20.f);

    selectionSort(shop.begin(), shop.end(),
                  [](const auto &a, const auto &b)
                  {
                      return a._name > b._name;
                  });

    std::vector<expectedBook> result = {
        {"zeta", 10.f},
        {"mu", 20.f},
        {"alpha", 30.f}};

    CHECK(checkBookOrder(shop, result));
}

TEST(SORTBYCOST)
{
    bookShop shop(3);

    shop.setBook("zeta", 10.f);
    shop.setBook("alpha", 30.f);
    shop.setBook("mu", 20.f);

    selectionSort(shop.begin(), shop.end(),
                  [](const auto &a, const auto &b)
                  {
                      return a._cost < b._cost;
                  });

    std::vector<expectedBook> result = {
        {"zeta", 10.f},
        {"mu", 20.f},
        {"alpha", 30.f}};

    CHECK(checkBookOrder(shop, result));
}

TEST(REVERSESORTBYCOST)
{
    bookShop shop(3);

    shop.setBook("zeta", 10.f);
    shop.setBook("alpha", 30.f);
    shop.setBook("mu", 20.f);

    selectionSort(shop.begin(), shop.end(),
                  [](const auto &a, const auto &b)
                  {
                      return a._cost > b._cost;
                  });

    std::vector<expectedBook> result = {
        {"alpha", 30.f},
        {"mu", 20.f},
        {"zeta", 10.f}};

    CHECK(checkBookOrder(shop, result));
}

TEST(ARRAYEQUALSIZE)
{
    bookShop _b[4] = {
        bookShop(5),
        bookShop(5),
        bookShop(5),
        bookShop(5)};

    _b[0].setBook("Мастер и Маргарита", 25.50f);
    _b[1].setBook("Преступление и наказание", 18.00f);
    _b[2].setBook("1984", 22.90f);
    _b[3].setBook("Три товарища", 30.00f);

    selectionSort(
        _b,
        _b + 4,
        [](bookShop &a, bookShop &b)
        {
            return a.begin()->_cost < b.begin()->_cost;
        });

    bookShop _res[4] = {
        bookShop(5),
        bookShop(5),
        bookShop(5),
        bookShop(5)};

    _res[0].setBook("Преступление и наказание", 18.00f);
    _res[1].setBook("1984", 22.90f);
    _res[2].setBook("Мастер и Маргарита", 25.50f);
    _res[3].setBook("Три товарища", 30.00f);

    for (unsigned i = 0; i < 4; ++i)
    {
        CHECK(_res[i] == _b[i]);
    }
}

TEST(ARRAYSORTREVERSECOST)
{
    bookShop _b[4] = {
        bookShop(5),
        bookShop(5),
        bookShop(5),
        bookShop(5)};

    _b[0].setBook("Мастер и Маргарита", 25.50f);
    _b[1].setBook("Преступление и наказание", 18.00f);
    _b[2].setBook("1984", 22.90f);
    _b[3].setBook("Три товарища", 30.00f);

    selectionSort(
        _b,
        _b + 4,
        [](bookShop &a, bookShop &b)
        {
            return a.begin()->_cost > b.begin()->_cost;
        });

    bookShop _res[4] = {
        bookShop(5),
        bookShop(5),
        bookShop(5),
        bookShop(5)};

    _res[0].setBook("Три товарища", 30.00f);
    _res[1].setBook("Мастер и Маргарита", 25.50f);
    _res[2].setBook("1984", 22.90f);
    _res[3].setBook("Преступление и наказание", 18.00f);

    for (unsigned i = 0; i < 4; ++i)
    {
        CHECK(_res[i] == _b[i]);
    }
}

TEST(ARRAYSORTBYNAME)
{
    bookShop _b[4] = {
        bookShop(5),
        bookShop(5),
        bookShop(5),
        bookShop(5)};

    _b[0].setBook("Мастер и Маргарита", 25.50f);
    _b[1].setBook("Преступление и наказание", 18.00f);
    _b[2].setBook("1984", 22.90f);
    _b[3].setBook("Три товарища", 30.00f);

    selectionSort(
        _b,
        _b + 4,
        [](bookShop &a, bookShop &b)
        {
            return a.begin()->_name < b.begin()->_name;
        });

    bookShop _res[4] = {
        bookShop(5),
        bookShop(5),
        bookShop(5),
        bookShop(5)};

    _res[0].setBook("1984", 22.90f);
    _res[1].setBook("Мастер и Маргарита", 25.50f);
    _res[2].setBook("Преступление и наказание", 18.00f);
    _res[3].setBook("Три товарища", 30.00f);

    for (unsigned i = 0; i < 4; ++i)
    {
        CHECK(_res[i] == _b[i]);
    }
}