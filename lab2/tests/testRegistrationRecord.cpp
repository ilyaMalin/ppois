#include <UnitTest++/UnitTest++.h>
#include "registration/registrationRecord.hpp"
#include <string>
#include "documents/document.hpp"

TEST(registrationRecordTest)
{
    registrationRecord value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.validateRegistration());
    registrationRecord invalid("", "");
    CHECK(!invalid.validateRegistration());
    value.cancelRegistration();
    CHECK_EQUAL(std::string("cancelregistration"), value.getStatus());
    document related("relatedId", "relatedName");
    value.linkDocument(related);
}
