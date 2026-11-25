#include "archive/archiveRecord.hpp"

#include <utility>

archiveRecord::archiveRecord(std::string id, std::string name)
    : id(std::move(id)), name(std::move(name)) {}

const std::string &archiveRecord::getName() const
{
    return name;
}

const std::string &archiveRecord::getStatus() const
{
    return status;
}

bool archiveRecord::validateArchiveRecord() const
{
    return !id.empty() && !name.empty();
}

void archiveRecord::archiveDocument()
{
    status = "archive";
}

void archiveRecord::linkDocument(document &value)
{
    documentRef = &value;
}
