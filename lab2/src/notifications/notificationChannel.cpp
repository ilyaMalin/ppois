#include "notifications/notificationChannel.hpp"

#include <utility>

notificationChannel::notificationChannel(std::string id, std::string name)
    : id(std::move(id)), name(std::move(name)) {}

const std::string &notificationChannel::getName() const
{
    return name;
}

const std::string &notificationChannel::getStatus() const
{
    return status;
}

bool notificationChannel::validateChannel() const
{
    return !id.empty() && !name.empty();
}

void notificationChannel::activateChannel()
{
    status = "activatechannel";
}
