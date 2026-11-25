#pragma once

#include <string>
#include "common/forward.hpp"

class archiveStorage
{
    std::string id;
    std::string name;
    std::string status;
    fileStorage *fileStorageRef = nullptr;

public:
    archiveStorage(std::string = {}, std::string = {});
    const std::string &getName() const;
    const std::string &getStatus() const;
    bool validateArchiveStorage() const;
    void openArchiveStorage();
    void linkFileStorage(fileStorage &);
};
