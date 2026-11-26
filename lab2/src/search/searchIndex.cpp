#include "search/searchIndex.hpp"

#include <utility>

searchIndex::searchIndex(std::string id, std::string name)
    : id(std::move(id)), name(std::move(name)) {}

const std::string &searchIndex::getName() const
{
    return name;
}

const std::string &searchIndex::getStatus() const
{
    return status;
}

bool searchIndex::validateSearchIndex() const
{
    return !id.empty() && !name.empty();
}

void searchIndex::rebuildSearchIndex()
{
    status = "rebuildsearchindex";
}

void searchIndex::linkDocument(document &value)
{
    documentRef = &value;
}
