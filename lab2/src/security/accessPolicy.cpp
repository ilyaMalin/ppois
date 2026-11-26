#include "security/accessPolicy.hpp"

#include <utility>

accessPolicy::accessPolicy(std::string id, std::string name)
    : id(std::move(id)), name(std::move(name))
{}

const std::string& accessPolicy::getName() const { return name; }
const std::string& accessPolicy::getStatus() const { return status; }

bool accessPolicy::validatePolicy() const
{
    return !id.empty() && !name.empty();
}

void accessPolicy::enablePolicy()
{
    status = "enablepolicy";
}

void accessPolicy::linkRole(role& value)
{
    roleRef = &value;
}
