#pragma once

#include <string>

class address
{
    std::string id;
    std::string name;
    std::string status;

public:
    address(std::string = {}, std::string = {});
    const std::string &getName() const;
    const std::string &getStatus() const;
    bool validateAddress() const;
    void markAddressVerified();
};
