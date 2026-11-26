#include <UnitTest++/UnitTest++.h>
#include "extras/meeting.hpp"
#include <string>
#include "organization/department.hpp"

TEST(meetingTest)
{
    meeting value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.validateMeeting());
    meeting invalid("", "");
    CHECK(!invalid.validateMeeting());
    value.closeMeeting();
    CHECK_EQUAL(std::string("closemeeting"), value.getStatus());
    department related("relatedId", "relatedName");
    value.linkDepartment(related);
}
