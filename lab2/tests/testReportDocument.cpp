#include <UnitTest++/UnitTest++.h>
#include "documents/reportDocument.hpp"
#include <string>
#include "reports/reportPeriod.hpp"

TEST(reportDocumentTest)
{
    reportDocument value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.finalizeReport());
    reportDocument invalid("", "");
    CHECK(!invalid.finalizeReport());
    value.publishReport();
    CHECK_EQUAL(std::string("publishreport"), value.getStatus());
    reportPeriod related("relatedId", "relatedName");
    value.linkReportPeriod(related);
}
