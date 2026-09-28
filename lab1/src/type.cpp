#include "../include/type.hpp"
#include "../include/multiset.hpp"

std::string &element::getStringValue()
{
    if (this->stringValue)
    {
        return *this->stringValue;
    }

    throw std::runtime_error("elementValue != string || !elementValue");
}

multiset *element::getSetValue() const
{
    if (this->setValue)
    {
        return this->setValue.get();
    }

    return nullptr;
}

bool element::operator==(const element &otherElement) const
{
    if (this->stringValue && otherElement.stringValue)
    {
        return this->stringValue == otherElement.stringValue;
    }

    if (this->setValue && otherElement.getSetValue())
    {
        return *this->getSetValue() == *otherElement.getSetValue();
    }

    return false;
}