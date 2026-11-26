#include <UnitTest++/UnitTest++.h>
#include "security/session.hpp"
#include <string>
#include "security/userAccount.hpp"

TEST(sessionTest)
{
    session value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.validateSession());
    session invalid("", "");
    CHECK(!invalid.validateSession());
    value.closeSession();
    CHECK_EQUAL(std::string("closesession"), value.getStatus());
    userAccount related("relatedId", "relatedName");
    value.linkUserAccount(related);
}
