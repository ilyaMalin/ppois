#include <UnitTest++/UnitTest++.h>
#include "signatures/certificate.hpp"
#include <string>
#include "organization/employee.hpp"

TEST(certificateTest)
{
    certificate value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.validateCertificate());
    certificate invalid("", "");
    CHECK(!invalid.validateCertificate());
    value.revokeCertificate();
    CHECK_EQUAL(std::string("revokecertificate"), value.getStatus());
    employee related("relatedId", "relatedName");
    value.linkEmployee(related);
}
