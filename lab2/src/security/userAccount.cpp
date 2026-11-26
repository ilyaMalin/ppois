#include "security/userAccount.hpp"

#include <utility>

userAccount::userAccount(std::string id, std::string name)
    : id(std::move(id)), name(std::move(name))
{}

const std::string& userAccount::getName() const { return name; }
const std::string& userAccount::getStatus() const { return status; }

bool userAccount::validateAccount() const
{
    return !id.empty() && !name.empty();
}

void userAccount::blockAccount()
{
    status = "blockaccount";
}

void userAccount::linkEmployee(employee& value)
{
    employeeRef = &value;
}
