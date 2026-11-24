#ifndef BOOKSHOP_HPP

#define BOOKSHOP_HPP
#include <vector>
#include <string>
#include <functional>
#include <algorithm>

class bookShop
{
public:
    struct book
    {
        std::string _name;
        float _cost;
    };

    using iterator = std::vector<book>::iterator;

    bookShop(unsigned);

    void setBook(const std::string &, const float &);
    float getCost(const std::string &) const;
    std::string getName(const float &) const;
    unsigned getMaxAmount() const;

    bool operator==(const bookShop &) const;

    iterator begin();
    iterator end();

private:
    std::vector<book> _book;
};

#endif