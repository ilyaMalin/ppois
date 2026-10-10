#ifndef MULTISET_HPP

#define MULTISET_HPP
#include "type.hpp"
#include <map>

class multiset
{
private:
    std::map<element, size_t> multiplicity;
    size_t cardinal = 0;

    bool parser(const std::string &, int &);

public:
    multiset() = default;
    explicit multiset(const char *);
    explicit multiset(std::string &);
    explicit multiset(const element &);
    multiset(const multiset &);

    multiset &operator=(const multiset &);

    bool empty() const;

    void insert(const element &);
    void insert(const multiset &);
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

    multiset buildBoolean();

    friend std::ostream &operator<<(std::ostream &, const multiset &);
    friend std::istream &operator>>(std::istream &, multiset &);
};

class storageMultiset
{
private:
    std::map<std::string, multiset> storage;

public:
    multiset &operator[](const std::string &);

    bool insert(const std::string &, const multiset &);
    bool remove(const std::string &);

    bool empty() const;

    std::map<std::string, multiset>::iterator begin();
    std::map<std::string, multiset>::iterator end();
};

#endif