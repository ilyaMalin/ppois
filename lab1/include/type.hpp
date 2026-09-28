#ifndef TYPE_HPP

#define TYPE_HPP
#include <iostream>
#include <memory>
#include <string>

class multiset;

class element
{
private:
    std::unique_ptr<std::string> stringValue = nullptr;
    std::unique_ptr<multiset> setValue = nullptr;

public:
    std::string &getStringValue();
    multiset *getSetValue() const;

    bool operator==(const element &) const;
};

#endif