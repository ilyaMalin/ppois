#include "search/searchQuery.hpp"

#include <utility>

searchQuery::searchQuery(std::string id, std::string name)
    : id(std::move(id)), name(std::move(name)) {}

const std::string &searchQuery::getName() const
{
    return name;
}

const std::string &searchQuery::getStatus() const
{
    return status;
}

bool searchQuery::validateSearchQuery() const
{
    return !id.empty() && !name.empty();
}

void searchQuery::clearSearchQuery()
{
    status = "clearsearchquery";
}

void searchQuery::linkEmployee(employee &value)
{
    employeeRef = &value;
}
