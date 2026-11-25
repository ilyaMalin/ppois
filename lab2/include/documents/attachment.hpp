#pragma once

#include <string>
#include "common/forward.hpp"

class attachment
{
    std::string id;
    std::string name;
    std::string status;
    fileStorage *fileStorageRef = nullptr;

public:
    attachment(std::string = {}, std::string = {});
    const std::string &getName() const;
    const std::string &getStatus() const;
    bool validateAttachment() const;
    void markAttachmentChecked();
    void linkFileStorage(fileStorage &);
};
