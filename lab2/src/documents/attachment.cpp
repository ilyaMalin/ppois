#include "documents/attachment.hpp"

#include <utility>

attachment::attachment(std::string id, std::string name)
    : id(std::move(id)), name(std::move(name)) {}

const std::string &attachment::getName() const
{
    return name;
}

const std::string &attachment::getStatus() const
{
    return status;
}

bool attachment::validateAttachment() const
{
    return !id.empty() && !name.empty();
}

void attachment::markAttachmentChecked()
{
    status = "markattachmentchecked";
}

void attachment::linkFileStorage(fileStorage &value)
{
    fileStorageRef = &value;
}
