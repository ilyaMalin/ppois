#pragma once

#include <string>
#include "common/forward.hpp"
class userAccount;

class session
{
    std::string id;
    std::string name;
    std::string status;
    userAccount* userAccountRef = nullptr;

public:
    session(std::string id = {}, std::string name = {});
    const std::string& getName() const;
    const std::string& getStatus() const;
    bool validateSession() const;
    void closeSession();
    void linkUserAccount(userAccount& value);
};
