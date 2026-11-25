#include "organization/department.hpp"

#include <utility>

department::department(std::string id, std::string name)
    : id(std::move(id)), name(std::move(name)) {}

const std::string &department::getName() const
{
    return name;
}

const std::string &department::getStatus() const
{
    return status;
}

bool department::validateDepartment() const
{
    return !id.empty() && !name.empty();
}

void department::openDepartment()
{
    status = "opendepartment";
}
