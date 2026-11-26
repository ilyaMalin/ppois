#include "security/session.hpp"

#include <utility>

session::session(std::string id, std::string name)
    : id(std::move(id)), name(std::move(name))
{}

const std::string& session::getName() const { return name; }
const std::string& session::getStatus() const { return status; }

bool session::validateSession() const
{
    return !id.empty() && !name.empty();
}

void session::closeSession()
{
    status = "closesession";
}

void session::linkUserAccount(userAccount& value)
{
    userAccountRef = &value;
}
