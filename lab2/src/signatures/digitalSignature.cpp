#include "signatures/digitalSignature.hpp"

#include <utility>

digitalSignature::digitalSignature(std::string id, std::string name)
    : id(std::move(id)), name(std::move(name)) {}

const std::string &digitalSignature::getName() const
{
    return name;
}

const std::string &digitalSignature::getStatus() const
{
    return status;
}

bool digitalSignature::validateSignature() const
{
    return !id.empty() && !name.empty();
}

void digitalSignature::signDocument()
{
    status = "sign";
}

void digitalSignature::linkCertificate(certificate &value)
{
    certificateRef = &value;
}
