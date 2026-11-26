#include "extras/meeting.hpp"

#include <utility>

meeting::meeting(std::string id, std::string name)
    : id(std::move(id)), name(std::move(name)) {}

const std::string &meeting::getName() const
{
    return name;
}

const std::string &meeting::getStatus() const
{
    return status;
}

bool meeting::validateMeeting() const
{
    return !id.empty() && !name.empty();
}

void meeting::closeMeeting()
{
    status = "closemeeting";
}

void meeting::linkDepartment(department &value)
{
    departmentRef = &value;
}
