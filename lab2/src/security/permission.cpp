#include "security/permission.hpp"

#include <utility>

permission::permission(std::string id, std::string name)
    : id(std::move(id)), name(std::move(name))
{}

const std::string& permission::getName() const { return name; }
const std::string& permission::getStatus() const { return status; }

bool permission::validatePermission() const
{
    return !id.empty() && !name.empty();
}

void permission::grantPermission()
{
    status = "grantpermission";
}

void permission::linkRole(role& value)
{
    roleRef = &value;
}
