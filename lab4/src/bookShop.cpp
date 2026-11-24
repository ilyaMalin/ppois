#include "bookShop.hpp"
#include "selectionSort.hpp"

bool bookShop::operator==(const bookShop &other) const
{
    if (this->_book.size() != other._book.size())
    {
        return false;
    }

    for (const auto &it : this->_book)
    {
        if (it._cost != other.getCost(it._name) && it._name != other.getName(it._cost))
        {
            return false;
        }
    }

    return true;
}

bookShop::bookShop(unsigned _maxAmountBook)
{
    this->_book.reserve(_maxAmountBook);
}

void bookShop::setBook(const std::string &_name, const float &_cost)
{
    if (this->_book.size() < this->_book.capacity())
    {
        this->_book.push_back({_name, _cost});
    }
}

float bookShop::getCost(const std::string &_name) const
{
    auto findedCost = std::find_if(this->_book.begin(), this->_book.end(), [&_name](const book &_book)
                                   { return _book._name == _name; });

    return findedCost != this->_book.end() ? findedCost->_cost : -1.f;
}

std::string bookShop::getName(const float &_cost) const
{
    auto findedName = std::find_if(this->_book.begin(), this->_book.end(), [&_cost](const book &_book)
                                   { return _book._cost == _cost; });

    return findedName != this->_book.end() ? findedName->_name : "";
}

unsigned bookShop::getMaxAmount() const
{
    return this->_book.capacity();
}

bookShop::iterator bookShop::begin()
{
    return _book.begin();
}

bookShop::iterator bookShop::end()
{
    return _book.end();
}
