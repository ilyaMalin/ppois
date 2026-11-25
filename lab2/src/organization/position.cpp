#include "organization/position.hpp"

#include <utility>

position::position(std::string id, std::string name)
    : id(std::move(id)), name(std::move(name)) {}

const std::string &position::getName() const
{
    return name;
}

const std::string &position::getStatus() const
{
    return status;
}

bool position::validatePosition() const
{
    return !id.empty() && !name.empty();
}

void position::activatePosition()
{
    status = "activateposition";
}

void position::linkDepartment(department &value)
{
    departmentRef = &value;
}
