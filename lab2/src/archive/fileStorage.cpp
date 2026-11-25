#include "archive/fileStorage.hpp"

#include <utility>

fileStorage::fileStorage(std::string id, std::string name)
    : id(std::move(id)), name(std::move(name)) {}

const std::string &fileStorage::getName() const
{
    return name;
}

const std::string &fileStorage::getStatus() const
{
    return status;
}

bool fileStorage::validateFileStorage() const
{
    return !id.empty() && !name.empty();
}

void fileStorage::checkStorageCapacity()
{
    status = "checkstoragecapacity";
}
