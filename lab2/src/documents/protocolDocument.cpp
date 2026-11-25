#include "documents/protocolDocument.hpp"

#include <utility>

protocolDocument::protocolDocument(std::string id, std::string name)
    : id(std::move(id)), name(std::move(name)) {}

const std::string &protocolDocument::getName() const
{
    return name;
}

const std::string &protocolDocument::getStatus() const
{
    return status;
}

bool protocolDocument::finalizeProtocol() const
{
    return !id.empty() && !name.empty();
}

void protocolDocument::publishProtocol()
{
    status = "publishprotocol";
}

void protocolDocument::linkMeeting(meeting &value)
{
    meetingRef = &value;
}
