#ifndef TYPE_HPP

#define TYPE_HPP
#include <vector>
#include <memory>
#include <string>

struct node
{
    std::string value;
    unsigned int countDuplicate = 0;
    std::unique_ptr<node> leftNode = nullptr;
    std::unique_ptr<node> right = nullptr;
    std::vector<std::vector<node *>> subset;

    node(const std::string &value) : value(value) {}
};

#endif