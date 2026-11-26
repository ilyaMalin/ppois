#pragma once

#include <string>

class notificationChannel
{
    std::string id;
    std::string name;
    std::string status;

public:
    notificationChannel(std::string = {}, std::string = {});
    const std::string &getName() const;
    const std::string &getStatus() const;
    bool validateChannel() const;
    void activateChannel();
};
