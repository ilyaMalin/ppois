#include <UnitTest++/UnitTest++.h>
#include "archive/fileStorage.hpp"
#include <string>

TEST(fileStorageTest)
{
    fileStorage value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.validateFileStorage());
    fileStorage invalid("", "");
    CHECK(!invalid.validateFileStorage());
    value.checkStorageCapacity();
    CHECK_EQUAL(std::string("checkstoragecapacity"), value.getStatus());
}
