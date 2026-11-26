#include <UnitTest++/UnitTest++.h>
#include "documents/documentVersion.hpp"
#include <string>
#include "documents/document.hpp"

TEST(documentVersionTest)
{
    documentVersion value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.compareVersions());
    documentVersion invalid("", "");
    CHECK(!invalid.compareVersions());
    value.restoreVersion();
    CHECK_EQUAL(std::string("restoreversion"), value.getStatus());
    document related("relatedId", "relatedName");
    value.linkDocument(related);
}
