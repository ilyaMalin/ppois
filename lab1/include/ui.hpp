#ifndef UI_HPP

#define UI_HPP
#include "multiset.hpp"
#include <limits>
#include <stack>

class UI
{
private:
    storageMultiset storage;

    void createMultiset(const multiset *);
    void destructMultiset();
    void viewMultiset();
    void performOperation();

    int getPriorityOperation(const char &) const;
    bool parser(const std::string &, std::string &) const;
    bool solver(const std::string &, multiset &);
    void saver(const multiset &);

public:
    void menu();
};

#endif