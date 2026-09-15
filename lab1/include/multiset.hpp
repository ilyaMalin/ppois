#ifndef MULTISET_HPP

#define MULTISET_HPP
#include "type.hpp"

class multiset
{
private:
    std::unique_ptr<node> set;

public:
    multiset();
    multiset(const std::string &);
    multiset(const std::vector<node *> &);

    void insert(const std::string &);
    void insert(const std::vector<node *> &);

    void remove(const std::string &);
    void remove(const std::vector<node *> &);

    bool contains(const std::string &) const;
    bool contains(const std::vector<node *> &) const;

    multiset buildBoolean();
};

#endif