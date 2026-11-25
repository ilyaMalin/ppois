#pragma once

#include <string>
#include "common/forward.hpp"

class archiveRecord
{
    std::string id;
    std::string name;
    std::string status;
    document *documentRef = nullptr;

public:
    archiveRecord(std::string = {}, std::string = {});
    const std::string &getName() const;
    const std::string &getStatus() const;
    bool validateArchiveRecord() const;
    void archiveDocument();
    void linkDocument(document &);
};
