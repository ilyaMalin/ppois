#include "../include/multiset.hpp"

multiset::multiset(const char *stringC)
{
    element elem;
    elem.setStringValue(stringC);
    this->set.push_back(elem);
    this->multiplicity[elem]++;
    this->cardinal++;
    std::cout << "Constructor param=const char *\n";
}

multiset::multiset(std::string &string)
{
    element elem;
    elem.setStringValue(string);
    this->set.push_back(elem);
    this->multiplicity[elem]++;
    this->cardinal++;
    std::cout << "Constructor param=const string &\n";
}

bool multiset::empty() const
{
    return this->set.empty();
}

void multiset::insert(const element &element)
{
    this->set.push_back(element);
    this->multiplicity[element]++;
    cardinal++;
}

// void multiset::remove(const element &) {}

size_t multiset::cardinality() const
{
    return this->cardinal;
}

bool multiset::operator[](const element &otherElement) const
{
    return this->multiplicity.contains(otherElement);
}

/*multiset &multiset::operator+(const multiset &) {}
multiset &multiset::operator+=(const multiset &) {}

multiset &multiset::operator*(const multiset &) {}
multiset &multiset::operator*=(const multiset &) {}

multiset &multiset::operator-(const multiset &) {}
multiset &multiset::operator-=(const multiset &) {}
*/
bool multiset::operator==(const multiset &otherSet) const
{
    return this->multiplicity == otherSet.multiplicity;
}

bool multiset::operator!=(const multiset &otherSet) const
{
    return !(*this == otherSet);
}

bool multiset::operator<(const multiset &otherSet) const
{
    if (this->cardinal != otherSet.cardinal)
    {
        return this->cardinal < otherSet.cardinal;
    }

    return this->multiplicity < otherSet.multiplicity;
}

bool multiset::operator>(const multiset &otherSet) const
{
    if (*this == otherSet)
    {
        return false;
    }

    return otherSet < *this;
}

multiset multiset::buildBoolean()
{
    size_t countElement = this->cardinality();
    size_t countSubset = 1 << countElement;

    multiset boolean;
    boolean.set.resize(countSubset);

    for (size_t i = 0; i < countSubset; i++)
    {
        multiset subSet;
        for (size_t j = 0; j < countElement; j++)
        {
            if (i & (1 << j))
            {
                subSet.insert(this->set[j]);
            }
        }

        boolean.set[i].setSetValue(subSet);
    }

    return boolean;
}

std::ostream &operator<<(std::ostream &os, const multiset &multiset)
{
    os << '{';
    for (size_t i = 0; i < multiset.set.size(); ++i)
    {
        if (i > 0)
        {
            os << ", ";
        }

        os << multiset.set[i];
    }

    os << '}';

    return os;
}