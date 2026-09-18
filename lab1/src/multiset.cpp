#include "../include/multiset.hpp"

multiset::multiset()
{
    std::cout << "Constructor without param\n";
}

multiset::multiset(const char *stringC)
{
    *this->set.begin()->getStringValue() = stringC;
    std::cout << "Constructor param=const char *\n";
}

multiset::multiset(std::string &string)
{
    *this->set.begin()->getStringValue() = string;
    std::cout << "Constructor param=const string &\n";
}

bool multiset::empty() const
{
    return this->set.empty();
}

void multiset::insert(const element &element)
{
    if (element.empty())
    {
        return;
    }

    this->set.push_back(element);
}
void multiset::remove(const element &) {}

size_t multiset::cardinality() const
{
    return this->set.size();
}

bool multiset::operator[](const element &) const {}

multiset &multiset::operator+(const element &) {}
multiset &multiset::operator+=(const element &) {}

multiset &multiset::operator*(const element &) {}
multiset &multiset::operator*=(const element &) {}

multiset &multiset::operator-(const element &) {}
multiset &multiset::operator-=(const element &) {}

bool multiset::operator==(const element &) const {}
bool multiset::operator!=(const element &) const {}

multiset buildBoolean() {}