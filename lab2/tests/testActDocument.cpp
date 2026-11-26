#include <UnitTest++/UnitTest++.h>
#include "documents/actDocument.hpp"
#include <string>
#include "organization/counterparty.hpp"

TEST(actDocumentTest)
{
    actDocument value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.confirmAct());
    actDocument invalid("", "");
    CHECK(!invalid.confirmAct());
    value.revokeAct();
    CHECK_EQUAL(std::string("revokeact"), value.getStatus());
    counterparty related("relatedId", "relatedName");
    value.linkCounterparty(related);
}
