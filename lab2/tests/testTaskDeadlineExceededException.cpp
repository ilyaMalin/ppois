#include <UnitTest++/UnitTest++.h>
#include "exceptions/documentManagementException.hpp"
#include <string>

TEST(taskDeadlineExceededExceptionTest)
{
    taskDeadlineExceededException value("test message");
    CHECK(std::string(value.what()) == "test message");
}
