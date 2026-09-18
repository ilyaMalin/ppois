#ifndef MULTISET_HPP

#define MULTISET_HPP
#include "type.hpp"
#include <vector>

class multiset
{
private:
    std::vector<element> set;

public:
    multiset();
    multiset(const char *);
    multiset(std::string &);

    bool empty() const;

    void insert(const element &);
    void remove(const element &);

    size_t cardinality() const;

    bool operator[](const element &) const;

    multiset &operator+(const element &);
    multiset &operator+=(const element &);

    multiset &operator*(const element &);
    multiset &operator*=(const element &);

    multiset &operator-(const element &);
    multiset &operator-=(const element &);

    bool operator==(const element &) const;
    bool operator!=(const element &) const;

    multiset buildBoolean();
};

#endif