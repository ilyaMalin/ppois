#pragma once

#include <string>
#include "common/forward.hpp"

class document
{
    std::string id;
    std::string name;
    std::string status;
    employee *employeeRef = nullptr;

public:
    document(std::string = {}, std::string = {});
    const std::string &getName() const;
    const std::string &getStatus() const;
    bool prepareDocument() const;
    void submitDocument();
    void linkEmployee(employee &);
};
