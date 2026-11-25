#include "documents/memoDocument.hpp"

#include <utility>

memoDocument::memoDocument(std::string id, std::string name)
    : id(std::move(id)), name(std::move(name)) {}

const std::string &memoDocument::getName() const
{
    return name;
}

const std::string &memoDocument::getStatus() const
{
    return status;
}

bool memoDocument::submitMemo() const
{
    return !id.empty() && !name.empty();
}

void memoDocument::withdrawMemo()
{
    status = "withdrawmemo";
}

void memoDocument::linkEmployee(employee &value)
{
    employeeRef = &value;
}
