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
    element() = default;
    element(const element &);

    std::string &getStringValue();
    multiset *getSetValue() const;

    void setStringValue(const std::string &);
    void setStringValue(const char *);
    void setSetValue(const multiset &);

    bool operator==(const element &) const;
    bool operator<(const element &) const;
    bool operator>(const element &) const;

    friend std::ostream &operator<<(std::ostream &, const element &);
};

#endif