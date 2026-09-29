#ifndef MULTISET_HPP

#define MULTISET_HPP
#include <stdexcept>
#include "type.hpp"
#include <map>

class multiset
{
private:
    std::map<element, size_t> multiplicity;
    size_t cardinal = 0;

public:
    multiset() = default;
    multiset(const char *);
    multiset(std::string &);
    multiset(const multiset &);

    bool empty() const;

    void insert(const element &);
    void remove(const element &);

    size_t cardinality() const;

    bool operator[](const element &) const;
    multiset operator+(const multiset &);
    multiset &operator+=(const multiset &);

    multiset operator*(const multiset &);
    multiset &operator*=(const multiset &);

    multiset operator-(const multiset &);
    multiset &operator-=(const multiset &);

    bool operator==(const multiset &) const;
    bool operator!=(const multiset &) const;
    bool operator<(const multiset &) const;
    bool operator>(const multiset &) const;

    // multiset buildBoolean();

    // friend std::ostream &operator<<(std::ostream &, const multiset &);
};

#endif