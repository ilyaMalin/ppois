#ifndef TYPE_HPP

#define TYPE_HPP
#include <iostream>
#include <string>

class multiset;

class element
{
private:
    std::string *stringValue = nullptr;
    multiset *setValue = nullptr;

public:
    std::string *getStringValue() const;
    multiset *getSetValue() const;

    bool operator==(const element &) const;

    bool empty() const;
};

#endif