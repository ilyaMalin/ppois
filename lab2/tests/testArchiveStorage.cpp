#include <UnitTest++/UnitTest++.h>
#include "archive/archiveStorage.hpp"
#include <string>
#include "archive/fileStorage.hpp"

TEST(archiveStorageTest)
{
    archiveStorage value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.validateArchiveStorage());
    archiveStorage invalid("", "");
    CHECK(!invalid.validateArchiveStorage());
    value.openArchiveStorage();
    CHECK_EQUAL(std::string("openarchivestorage"), value.getStatus());
    fileStorage related("relatedId", "relatedName");
    value.linkFileStorage(related);
}
