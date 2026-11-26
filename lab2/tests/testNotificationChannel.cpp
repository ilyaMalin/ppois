#include <UnitTest++/UnitTest++.h>
#include "notifications/notificationChannel.hpp"
#include <string>

TEST(notificationChannelTest)
{
    notificationChannel value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.validateChannel());
    notificationChannel invalid("", "");
    CHECK(!invalid.validateChannel());
    value.activateChannel();
    CHECK_EQUAL(std::string("activatechannel"), value.getStatus());
}
