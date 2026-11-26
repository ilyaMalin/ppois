#include <UnitTest++/UnitTest++.h>
#include "reports/reportPeriod.hpp"
#include <string>

TEST(reportPeriodTest)
{
    reportPeriod value("id", "name");
    CHECK_EQUAL(std::string("name"), value.getName());
    CHECK(value.getStatus().empty());
    CHECK(value.validateReportPeriod());
    reportPeriod invalid("", "");
    CHECK(!invalid.validateReportPeriod());
    value.closeReportPeriod();
    CHECK_EQUAL(std::string("closereportperiod"), value.getStatus());
}
