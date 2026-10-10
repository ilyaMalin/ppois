#include "multiset.hpp"

bool multiset::parser(const std::string &stringElement, int &pos)
{
    if (stringElement[pos] != '{')
    {
        return false;
    }

    pos++;

    while (pos < stringElement.size())
    {
        if (stringElement[pos] == '}')
        {
            pos++;
            return true;
        }

        if (stringElement[pos] == '{')
        {
            multiset elementSet;
            elementSet.parser(stringElement, pos);

            this->insert(elementSet);
        }
        else
        {
            std::string string = "";
            while (pos < stringElement.size() &&
                   stringElement[pos] != ',' && stringElement[pos] != '{' && stringElement[pos] != '}')
            {
                string += stringElement[pos++];
            }

            if (!string.empty())
            {
                element elementString;
                elementString.setStringValue(string);
                this->insert(elementString);
            }
        }

        if (pos < stringElement.size() && stringElement[pos] == ',')
        {
            pos++;
        }

        while (pos < stringElement.size() && stringElement[pos] == ' ')
        {
            pos++;
        }
    }

    return true;
}

multiset::multiset(const char *stringC)
{
    const std::string elem = stringC;
    int i = 0;
    this->parser(elem, i);
}

multiset::multiset(std::string &string)
{
    int i = 0;
    this->parser(string, i);
}

multiset::multiset(const element &otherElement)
{
    this->insert(otherElement);
}

multiset::multiset(const multiset &otherSet)
{
    this->cardinal = otherSet.cardinal;

    for (const auto &iterator : otherSet.multiplicity)
    {
        element newElement = iterator.first;

        this->multiplicity[newElement] = iterator.second;
    }
}

multiset &multiset::operator=(const multiset &otherSet)
{
    this->multiplicity = otherSet.multiplicity;
    this->cardinal = otherSet.cardinal;

    return *this;
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
            long long difference = iteratorThisSet->second - iteratorOtherSet->second;

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
                os << ", ";
            }

            os << iterator.first;
            multipl--;
            flag = true;
        }
    }

    os << '}';

    return os;
}

std::istream &operator>>(std::istream &is, multiset &set)
{
    std::cin.ignore();
    std::string elem;
    std::getline(is, elem);
    int i = 0;
    set.parser(elem, i);
    return is;
}

bool storageMultiset::insert(const std::string &nameSet, const multiset &otherSet)
{
    auto inserted = this->storage.try_emplace(nameSet, otherSet);
    return inserted.second;
}

bool storageMultiset::empty() const
{
    return this->storage.empty();
}

bool storageMultiset::remove(const std::string &nameSet)
{
    auto iterator = this->storage.find(nameSet);

    if (iterator != this->storage.end())
    {
        this->storage.erase(iterator);
        return true;
    }

    return false;
}

multiset &storageMultiset::operator[](const std::string &nameSet)
{
    auto iterator = this->storage.find(nameSet);

    if (iterator != this->storage.end())
    {
        return iterator->second;
    }
}

std::map<std::string, multiset>::iterator storageMultiset::begin()
{
    return this->storage.begin();
}

std::map<std::string, multiset>::iterator storageMultiset::end()
{
    return this->storage.end();
}