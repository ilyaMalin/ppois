#pragma once

#include <string>
#include "common/forward.hpp"

class orderDocument
{
    std::string id;
    std::string name;
    std::string status;
    employee *employeeRef = nullptr;

public:
    orderDocument(std::string = {}, std::string = {});
    const std::string &getName() const;
    const std::string &getStatus() const;
    bool issueOrder() const;
    void cancelOrder();
    void linkEmployee(employee &);
};
