#include "archive/archiveStorage.hpp"

#include <utility>

archiveStorage::archiveStorage(std::string id, std::string name)
    : id(std::move(id)), name(std::move(name)) {}

const std::string &archiveStorage::getName() const
{
    return name;
}

const std::string &archiveStorage::getStatus() const
{
    return status;
}

bool archiveStorage::validateArchiveStorage() const
{
    return !id.empty() && !name.empty();
}

void archiveStorage::openArchiveStorage()
{
    status = "openarchivestorage";
}

void archiveStorage::linkFileStorage(fileStorage &value)
{
    fileStorageRef = &value;
}
