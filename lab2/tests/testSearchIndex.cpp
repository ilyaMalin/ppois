#include <UnitTest++/UnitTest++.h>
#include "search/searchIndex.hpp"
#include <string>
#include "documents/document.hpp"

TEST(searchIndexTest)
{
    searchIndex value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.validateSearchIndex());
    searchIndex invalid("", "");
    CHECK(!invalid.validateSearchIndex());
    value.rebuildSearchIndex();
    CHECK_EQUAL(std::string("rebuildsearchindex"), value.getStatus());
    document related("relatedId", "relatedName");
    value.linkDocument(related);
}
