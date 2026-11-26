#pragma once

#include <string>
#include "common/forward.hpp"

class searchQuery
{
    std::string id;
    std::string name;
    std::string status;
    employee *employeeRef = nullptr;

public:
    searchQuery(std::string = {}, std::string = {});
    const std::string &getName() const;
    const std::string &getStatus() const;
    bool validateSearchQuery() const;
    void clearSearchQuery();
    void linkEmployee(employee &);
};
