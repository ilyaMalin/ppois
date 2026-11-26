#pragma once

#include <string>
#include "common/forward.hpp"

class certificate
{
    std::string id;
    std::string name;
    std::string status;
    employee *employeeRef = nullptr;

public:
    certificate(std::string = {}, std::string = {});
    const std::string &getName() const;
    const std::string &getStatus() const;
    bool validateCertificate() const;
    void revokeCertificate();
    void linkEmployee(employee &);
};
