#pragma once

#include <string>
#include "common/forward.hpp"

class protocolDocument
{
    std::string id;
    std::string name;
    std::string status;
    meeting *meetingRef = nullptr;

public:
    protocolDocument(std::string = {}, std::string = {});
    const std::string &getName() const;
    const std::string &getStatus() const;
    bool finalizeProtocol() const;
    void publishProtocol();
    void linkMeeting(meeting &);
};
