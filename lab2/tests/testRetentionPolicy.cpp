#include <UnitTest++/UnitTest++.h>
#include "archive/retentionPolicy.hpp"
#include <string>
#include "documents/documentType.hpp"

TEST(retentionPolicyTest)
{
    retentionPolicy value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.validateRetentionPolicy());
    retentionPolicy invalid("", "");
    CHECK(!invalid.validateRetentionPolicy());
    value.applyRetentionPolicy();
    CHECK_EQUAL(std::string("applyretentionpolicy"), value.getStatus());
    documentType related("relatedId", "relatedName");
    value.linkDocumentType(related);
}
