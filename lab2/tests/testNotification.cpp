#include <UnitTest++/UnitTest++.h>
#include "notifications/notification.hpp"
#include <string>
#include "security/userAccount.hpp"

TEST(notificationTest)
{
    notification value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.validateNotification());
    notification invalid("", "");
    CHECK(!invalid.validateNotification());
    value.sendNotification();
    CHECK_EQUAL(std::string("sendnotification"), value.getStatus());
    userAccount related("relatedId", "relatedName");
    value.linkUserAccount(related);
}
