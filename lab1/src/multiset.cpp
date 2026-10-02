#include "../include/multiset.hpp"

multiset::multiset(const char *stringC)
{
    element elem;
    elem.setStringValue(stringC);
    this->insert(elem);
}

multiset::multiset(std::string &string)
{
    element elem;
    elem.setStringValue(string);
    this->insert(elem);
}

multiset::multiset(const element &otherElement)
{
    this->insert(otherElement);
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

void multiset::insert(const multiset &otherSet)
{
    element elem;
    elem.setSetValue(otherSet);
    this->insert(elem);
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

multiset multiset::buildBoolean()
{
    multiset emptySet;
    multiset boolean;

    boolean.insert(emptySet);

    for (const auto &iteratorThisSet : this->multiplicity)
    {
        multiset group = boolean;
        size_t multipl = iteratorThisSet.second;

        multiset currentSubSet(iteratorThisSet.first);
        while (multipl != 0)
        {
            for (const auto &iteratorGroup : boolean.multiplicity)
            {
                multiset combination = *iteratorGroup.first.getSetValue();

                combination += currentSubSet;
                group.insert(combination);
            }

            multipl--;
            currentSubSet.insert(iteratorThisSet.first);
        }

        boolean = group;
    }

    return boolean;
}

std::ostream &operator<<(std::ostream &os, const multiset &multiset)
{
    os << '{';

    bool flag = false;
    for (const auto &iterator : multiset.multiplicity)
    {
        size_t multipl = iterator.second;

        while (multipl != 0)
        {
            if (flag)
            {
                std::cout << ", ";
            }

            os << iterator.first;
            multipl--;
            flag = true;
        }
    }

    os << '}';

    return os;
}