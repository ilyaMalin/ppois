#include <UnitTest++/UnitTest++.h>
#include "registration/deliveryRecord.hpp"
#include <string>
#include "documents/outgoingDocument.hpp"

TEST(deliveryRecordTest)
{
    deliveryRecord value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.validateDelivery());
    deliveryRecord invalid("", "");
    CHECK(!invalid.validateDelivery());
    value.confirmDelivery();
    CHECK_EQUAL(std::string("confirmdelivery"), value.getStatus());
    outgoingDocument related("relatedId", "relatedName");
    value.linkOutgoingDocument(related);
}
