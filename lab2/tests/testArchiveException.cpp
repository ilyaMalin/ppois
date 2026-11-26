#include <UnitTest++/UnitTest++.h>
#include "exceptions/documentManagementException.hpp"
#include <string>

TEST(archiveExceptionTest)
{
    archiveException value("test message");
    CHECK(std::string(value.what()) == "test message");
}
