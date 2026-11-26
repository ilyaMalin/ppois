#pragma once

#include <string>
#include "common/forward.hpp"

class notification
{
    std::string id;
    std::string name;
    std::string status;
    userAccount *userAccountRef = nullptr;

public:
    notification(std::string = {}, std::string = {});
    const std::string &getName() const;
    const std::string &getStatus() const;
    bool validateNotification() const;
    void sendNotification();
    void linkUserAccount(userAccount &);
};
