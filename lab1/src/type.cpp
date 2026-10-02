#include "../include/type.hpp"
#include "../include/multiset.hpp"

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

std::string &element::getStringValue()
{
    if (this->stringValue)
    {
        return *this->stringValue;
    }

    throw std::runtime_error("elementValue != string");
}

multiset *element::getSetValue() const
{
    if (this->setValue)
    {
        return this->setValue.get();
    }

    return nullptr;
}

void element::setStringValue(const std::string &stringValue)
{
    this->stringValue = std::make_unique<std::string>(stringValue);
}

void element::setStringValue(const char *stringCValue)
{
    this->stringValue = std::make_unique<std::string>(stringCValue);
}

void element::setSetValue(const multiset &setValue)
{
    this->setValue = std::make_unique<multiset>(setValue);
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
    if (this->stringValue && otherElement.setValue)
    {
        return false;
    }
    else if (this->stringValue && otherElement.stringValue)
    {
        return *this->stringValue < *otherElement.stringValue;
    }
    else if (this->setValue && otherElement.stringValue)
    {
        return true;
    }

    return *this->setValue < *otherElement.setValue;
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