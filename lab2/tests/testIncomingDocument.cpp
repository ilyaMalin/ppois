#include <UnitTest++/UnitTest++.h>
#include "documents/incomingDocument.hpp"
#include <string>
#include "organization/counterparty.hpp"

TEST(incomingDocumentTest)
{
    incomingDocument value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.recordReceipt());
    incomingDocument invalid("", "");
    CHECK(!invalid.recordReceipt());
    value.markIncomingReviewed();
    CHECK_EQUAL(std::string("markincomingreviewed"), value.getStatus());
    counterparty related("relatedId", "relatedName");
    value.linkCounterparty(related);
}
