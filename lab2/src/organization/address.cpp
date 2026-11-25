#include "organization/address.hpp"

#include <utility>

address::address(std::string id, std::string name)
    : id(std::move(id)), name(std::move(name)) {}

const std::string &address::getName() const
{
    return name;
}

const std::string &address::getStatus() const
{
    return status;
}

bool address::validateAddress() const
{
    return !id.empty() && !name.empty();
}

void address::markAddressVerified()
{
    status = "markaddressverified";
}
