#include "../include/type.hpp"

std::string *element::getStringValue() const
{
    return this->stringValue;
}

multiset *element::getSetValue() const
{
    return this->setValue;
}

// СДЕЛАТЬ !!!!!!!!!!!!!!!!!!!!!!!
// + СРАВНЕНИЕ МНОЖЕСТВ
bool element::operator==(const element &element) const
{
    if (this->empty() && element.empty())
    {
        return true;
    }

    if (*this->stringValue == *element.getStringValue())
    {
        return true;
    } 

    return false;
}

bool element::empty() const
{
    return !this->setValue && !this->stringValue;
}