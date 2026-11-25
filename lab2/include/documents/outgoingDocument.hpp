#pragma once

#include <string>
#include "common/forward.hpp"

class outgoingDocument
{
    std::string id;
    std::string name;
    std::string status;
    counterparty *counterpartyRef = nullptr;

public:
    outgoingDocument(std::string = {}, std::string = {});
    const std::string &getName() const;
    const std::string &getStatus() const;
    bool prepareDispatch() const;
    void markOutgoingSent();
    void linkCounterparty(counterparty &);
};
