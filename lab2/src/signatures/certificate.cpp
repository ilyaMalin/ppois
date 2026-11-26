#include "signatures/certificate.hpp"

#include <utility>

certificate::certificate(std::string id, std::string name)
    : id(std::move(id)), name(std::move(name)) {}

const std::string &certificate::getName() const
{
    return name;
}

const std::string &certificate::getStatus() const
{
    return status;
}

bool certificate::validateCertificate() const
{
    return !id.empty() && !name.empty();
}

void certificate::revokeCertificate()
{
    status = "revokecertificate";
}

void certificate::linkEmployee(employee &value)
{
    employeeRef = &value;
}
