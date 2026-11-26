#include <UnitTest++/UnitTest++.h>
#include "workflow/reminder.hpp"
#include <string>
#include "workflow/task.hpp"

TEST(reminderTest)
{
    reminder value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.validateReminder());
    reminder invalid("", "");
    CHECK(!invalid.validateReminder());
    value.sendReminder();
    CHECK_EQUAL(std::string("sendreminder"), value.getStatus());
    task related("relatedId", "relatedName");
    value.linkTask(related);
}
