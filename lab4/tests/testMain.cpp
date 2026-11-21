#include <iostream>
#include "UnitTest++/UnitTest++.h"
#include "UnitTest++/TestReporter.h"
#include "UnitTest++/TestRunner.h"
#include "UnitTest++/TestDetails.h"

class CustomReporter : public UnitTest::TestReporter
{
private:
    bool currentTestFailed = false;

public:
    void ReportTestStart(UnitTest::TestDetails const &test) override
    {
        currentTestFailed = false;
        std::cout << test.testName << " ---- ";
    }

    void ReportFailure(UnitTest::TestDetails const &test, char const *failure) override
    {
        currentTestFailed = true;
        std::cout << "FAIL (" << failure << " at line " << test.lineNumber << ") ";
    }

    void ReportTestFinish(UnitTest::TestDetails const &, float) override
    {
        if (!currentTestFailed)
        {
            std::cout << "PASSED";
        }
        std::cout << std::endl;
    }

    void ReportSummary(int totalTestCount, int failedTestCount, int failureCount, float secondsElapsed) override
    {
        std::cout << "\nAll tests: " << totalTestCount
                  << ", FAILED: " << failedTestCount
                  << " (" << secondsElapsed << " sec.)" << std::endl;
    }
};

int main()
{
    CustomReporter reporter;
    UnitTest::TestRunner runner(reporter);
    return runner.RunTestsIf(UnitTest::Test::GetTestList(), nullptr, UnitTest::True(), 0);
}