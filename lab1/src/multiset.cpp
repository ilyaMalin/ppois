#include "../include/multiset.hpp"

multiset::multiset(const char *stringC)
{
    element elem;
    elem.setStringValue(stringC);
    this->insert(elem);
    std::cout << "Constructor param=const char *\n";
}

multiset::multiset(std::string &string)
{
    element elem;
    elem.setStringValue(string);
    this->insert(elem);
    std::cout << "Constructor param=const string &\n";
}

multiset::multiset(const multiset &otherSet)
{
    if (*this == otherSet)
    {
        return;
    }

    this->cardinal = otherSet.cardinal;

    for (const auto &iterator : otherSet.multiplicity)
    {
        element newElement = iterator.first;

        this->multiplicity[newElement] = iterator.second;
    }
}

bool multiset::empty() const
{
    return this->cardinal == 0;
}

void multiset::insert(const element &element)
{
    this->multiplicity[element]++;
    this->cardinal++;
}

void multiset::remove(const element &otherElement)
{
    auto iterator = this->multiplicity.find(otherElement);

    if (iterator != this->multiplicity.end())
    {
        iterator->second--;
        this->cardinal--;

        if (iterator->second == 0)
        {
            this->multiplicity.erase(iterator);
        }
    }
}

size_t multiset::cardinality() const
{
    return this->cardinal;
}

bool multiset::operator[](const element &otherElement) const
{
    return this->multiplicity.contains(otherElement);
}

multiset multiset::operator+(const multiset &otherSet)
{
    multiset bufferSet(*this);
    bufferSet += otherSet;
    return bufferSet;
}

multiset &multiset::operator+=(const multiset &otherSet)
{
    for (const auto &iterator : otherSet.multiplicity)
    {
        size_t &multiplThisElement = this->multiplicity[iterator.first];
        this->multiplicity[iterator.first] = std::max(iterator.second, multiplThisElement);
    }

    this->cardinal = 0;
    for (const auto &iterator : this->multiplicity)
    {
        this->cardinal += iterator.second;
    }

    return *this;
}

multiset multiset::operator*(const multiset &otherSet)
{
    multiset bufferSet(*this);
    bufferSet *= otherSet;
    return bufferSet;
}

multiset &multiset::operator*=(const multiset &otherSet)
{
    auto iteratorThisSet = this->multiplicity.begin();

    while (iteratorThisSet != this->multiplicity.end())
    {
        auto iteratorOtherSet = otherSet.multiplicity.find(iteratorThisSet->first);

        if (iteratorOtherSet != otherSet.multiplicity.end())
        {
            iteratorThisSet->second = std::min(iteratorOtherSet->second, iteratorThisSet->second);
            iteratorThisSet++;
        }
        else
        {
            iteratorThisSet = this->multiplicity.erase(iteratorThisSet);
        }
    }

    this->cardinal = 0;
    for (const auto &iterator : this->multiplicity)
    {
        this->cardinal += iterator.second;
    }

    return *this;
}

multiset multiset::operator-(const multiset &otherSet)
{
    multiset bufferSet(*this);
    bufferSet -= otherSet;
    return bufferSet;
}

multiset &multiset::operator-=(const multiset &otherSet)
{
    auto iteratorThisSet = this->multiplicity.begin();

    while (iteratorThisSet != this->multiplicity.end())
    {
        const auto &iteratorOtherSet = otherSet.multiplicity.find(iteratorThisSet->first);

        if (iteratorOtherSet != otherSet.multiplicity.end())
        {
            size_t difference = iteratorThisSet->second - iteratorOtherSet->second;

            if (difference <= 0)
            {
                iteratorThisSet = this->multiplicity.erase(iteratorThisSet);
            }
            else
            {
                iteratorThisSet->second = difference;
                iteratorThisSet++;
            }
        }
        else
        {
            iteratorThisSet++;
        }
    }

    this->cardinal = 0;
    for (const auto &iterator : this->multiplicity)
    {
        this->cardinal += iterator.second;
    }

    return *this;
}

bool multiset::operator==(const multiset &otherSet) const
{
    return this->multiplicity == otherSet.multiplicity;
}

bool multiset::operator!=(const multiset &otherSet) const
{
    return this->multiplicity != otherSet.multiplicity;
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
    if (this->cardinal != otherSet.cardinal)
    {
        return this->cardinal > otherSet.cardinal;
    }

    return this->multiplicity > otherSet.multiplicity;
}

/*
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
*/
/*std::ostream &operator<<(std::ostream &os, const multiset &multiset)
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
}*/