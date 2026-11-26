#include "security/role.hpp"

#include <utility>

role::role(std::string id, std::string name)
    : id(std::move(id)), name(std::move(name))
{}

const std::string& role::getName() const { return name; }
const std::string& role::getStatus() const { return status; }

bool role::validateRole() const
{
    return !id.empty() && !name.empty();
}

void role::activateRole()
{
    status = "activaterole";
}
