#include "organization/employee.hpp"

#include <utility>

employee::employee(std::string id, std::string name)
    : id(std::move(id)), name(std::move(name)) {}

const std::string &employee::getName() const
{
    return name;
}

const std::string &employee::getStatus() const
{
    return status;
}

bool employee::validateEmployee() const
{
    return !id.empty() && !name.empty();
}

void employee::activateEmployee()
{
    status = "activateemployee";
}

void employee::linkDepartment(department &value)
{
    departmentRef = &value;
}
