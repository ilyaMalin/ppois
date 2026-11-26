#pragma once

#include <string>
#include "common/forward.hpp"

class searchIndex
{
    std::string id;
    std::string name;
    std::string status;
    document *documentRef = nullptr;

public:
    searchIndex(std::string = {}, std::string = {});
    const std::string &getName() const;
    const std::string &getStatus() const;
    bool validateSearchIndex() const;
    void rebuildSearchIndex();
    void linkDocument(document &);
};
