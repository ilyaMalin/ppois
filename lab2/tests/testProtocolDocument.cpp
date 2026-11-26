#include <UnitTest++/UnitTest++.h>
#include "documents/protocolDocument.hpp"
#include <string>
#include "extras/meeting.hpp"

TEST(protocolDocumentTest)
{
    protocolDocument value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.finalizeProtocol());
    protocolDocument invalid("", "");
    CHECK(!invalid.finalizeProtocol());
    value.publishProtocol();
    CHECK_EQUAL(std::string("publishprotocol"), value.getStatus());
    meeting related("relatedId", "relatedName");
    value.linkMeeting(related);
}
