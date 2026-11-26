#include <UnitTest++/UnitTest++.h>
#include "reports/reportGenerator.hpp"
#include <string>
#include "organization/department.hpp"

TEST(reportGeneratorTest)
{
    reportGenerator value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.validateReportRequest());
    reportGenerator invalid("", "");
    CHECK(!invalid.validateReportRequest());
    value.generateReport();
    CHECK_EQUAL(std::string("generatereport"), value.getStatus());
    department related("relatedId", "relatedName");
    value.linkDepartment(related);
}
