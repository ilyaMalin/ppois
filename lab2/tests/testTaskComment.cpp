#include <UnitTest++/UnitTest++.h>
#include "workflow/taskComment.hpp"
#include <string>
#include "workflow/task.hpp"

TEST(taskCommentTest)
{
    taskComment value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.validateComment());
    taskComment invalid("", "");
    CHECK(!invalid.validateComment());
    value.publishComment();
    CHECK_EQUAL(std::string("publishcomment"), value.getStatus());
    task related("relatedId", "relatedName");
    value.linkTask(related);
}
