#pragma once

#include <string>

class fileStorage
{
    std::string id;
    std::string name;
    std::string status;

public:
    fileStorage(std::string id = {}, std::string name = {});
    const std::string& getName() const;
    const std::string& getStatus() const;
    bool validateFileStorage() const;
    void checkStorageCapacity();
};
