#include <UnitTest++/UnitTest++.h>
#include "documents/attachment.hpp"
#include <string>
#include "archive/fileStorage.hpp"

TEST(attachmentTest)
{
    attachment value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.validateAttachment());
    attachment invalid("", "");
    CHECK(!invalid.validateAttachment());
    value.markAttachmentChecked();
    CHECK_EQUAL(std::string("markattachmentchecked"), value.getStatus());
    fileStorage related("relatedId", "relatedName");
    value.linkFileStorage(related);
}
