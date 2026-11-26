#include "notifications/notification.hpp"

#include <utility>

notification::notification(std::string id, std::string name)
    : id(std::move(id)), name(std::move(name)) {}

const std::string &notification::getName() const
{
    return name;
}

const std::string &notification::getStatus() const
{
    return status;
}

bool notification::validateNotification() const
{
    return !id.empty() && !name.empty();
}

void notification::sendNotification()
{
    status = "sendnotification";
}

void notification::linkUserAccount(userAccount &value)
{
    userAccountRef = &value;
}
