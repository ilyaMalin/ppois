#include "type.hpp"
#include "multiset.hpp"

element::element() = default;

element::~element() = default;

element::element(const element &other)
{
    if (other.stringValue)
    {
        this->stringValue = std::make_unique<std::string>(*other.stringValue);
    }
    else
    {
        this->setValue = std::make_unique<multiset>(*other.setValue);
    }
}

element &element::operator=(const element &otherElement)
{
    if (otherElement.stringValue)
    {
        this->stringValue = std::make_unique<std::string>(*otherElement.stringValue);
    }
    else
    {
        this->setValue = std::make_unique<multiset>(*otherElement.setValue);
    }

    return *this;
}

std::string *element::getStringValue() const
{
    return this->stringValue.get();
}

multiset *element::getSetValue() const
{
    return this->setValue.get();
}

void element::setStringValue(const std::string &value)
{
    this->stringValue = std::make_unique<std::string>(value);
}

void element::setStringValue(const char *cvalue)
{
    this->stringValue = std::make_unique<std::string>(cvalue);
}

void element::setSetValue(const multiset &value)
{
    this->setValue = std::make_unique<multiset>(value);
}

bool element::operator==(const element &otherElement) const
{
    if (this->stringValue && otherElement.stringValue)
    {
        return *this->stringValue == *otherElement.stringValue;
    }

    if (this->setValue && otherElement.setValue)
    {
        return *this->setValue == *otherElement.setValue;
    }

    return false;
}

bool element::operator<(const element &otherElement) const
{
    bool thisEmpty = !this->stringValue && !this->setValue;
    bool otherEmpty = !otherElement.stringValue && !otherElement.setValue;

    if (thisEmpty || otherEmpty)
    {
        return thisEmpty && !otherEmpty;
    }
    else if (this->stringValue && otherElement.stringValue)
    {
        return *this->stringValue < *otherElement.stringValue;
    }
    else if (this->setValue && otherElement.setValue)
    {
        return *this->setValue < *otherElement.setValue;
    }

    return static_cast<bool>(this->setValue);
}

bool element::operator>(const element &otherElement) const
{
    if (*this == otherElement)
    {
        return false;
    }

    return otherElement < *this;
}

std::ostream &operator<<(std::ostream &os, const element &element)
{
    if (element.stringValue)
    {
        os << *element.stringValue;
    }
    else
    {
        os << *element.setValue;
    }

    return os;
}