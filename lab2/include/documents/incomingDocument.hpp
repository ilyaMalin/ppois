#pragma once

#include <string>
#include "common/forward.hpp"

class incomingDocument
{
    std::string id;
    std::string name;
    std::string status;
    counterparty *counterpartyRef = nullptr;

public:
    incomingDocument(std::string = {}, std::string = {});
    const std::string &getName() const;
    const std::string &getStatus() const;
    bool recordReceipt() const;
    void markIncomingReviewed();
    void linkCounterparty(counterparty &);
};
