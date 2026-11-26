#include <UnitTest++/UnitTest++.h>
#include "exceptions/documentManagementException.hpp"
#include <string>

TEST(documentAlreadyRegisteredExceptionTest)
{
    documentAlreadyRegisteredException value("test message");
    CHECK(std::string(value.what()) == "test message");
}
