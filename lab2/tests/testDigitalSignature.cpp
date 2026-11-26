#include <UnitTest++/UnitTest++.h>
#include "signatures/digitalSignature.hpp"
#include <string>
#include "signatures/certificate.hpp"

TEST(digitalSignatureTest)
{
    digitalSignature value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.validateSignature());
    digitalSignature invalid("", "");
    CHECK(!invalid.validateSignature());
    value.signDocument();
    CHECK_EQUAL(std::string("sign"), value.getStatus());
    certificate related("relatedId", "relatedName");
    value.linkCertificate(related);
}
