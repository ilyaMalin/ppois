#include <UnitTest++/UnitTest++.h>
#include "archive/archiveRecord.hpp"
#include <string>
#include "documents/document.hpp"

TEST(archiveRecordTest)
{
    archiveRecord value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.validateArchiveRecord());
    archiveRecord invalid("", "");
    CHECK(!invalid.validateArchiveRecord());
    value.archiveDocument();
    CHECK_EQUAL(std::string("archive"), value.getStatus());
    document related("relatedId", "relatedName");
    value.linkDocument(related);
}
