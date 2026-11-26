#include <UnitTest++/UnitTest++.h>
#include "documents/outgoingDocument.hpp"
#include <string>
#include "organization/counterparty.hpp"

TEST(outgoingDocumentTest)
{
    outgoingDocument value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.prepareDispatch());
    outgoingDocument invalid("", "");
    CHECK(!invalid.prepareDispatch());
    value.markOutgoingSent();
    CHECK_EQUAL(std::string("markoutgoingsent"), value.getStatus());
    counterparty related("relatedId", "relatedName");
    value.linkCounterparty(related);
}
