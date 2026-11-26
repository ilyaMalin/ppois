#include <UnitTest++/UnitTest++.h>
#include "exceptions/documentManagementException.hpp"
#include <string>

TEST(invalidDocumentStatusExceptionTest)
{
    invalidDocumentStatusException value("test message");
    CHECK(std::string(value.what()) == "test message");
}
