#pragma once

#include <string>
#include "common/forward.hpp"

class memoDocument
{
    std::string id;
    std::string name;
    std::string status;
    employee *employeeRef = nullptr;

public:
    memoDocument(std::string = {}, std::string = {});
    const std::string &getName() const;
    const std::string &getStatus() const;
    bool submitMemo() const;
    void withdrawMemo();
    void linkEmployee(employee &);
};
