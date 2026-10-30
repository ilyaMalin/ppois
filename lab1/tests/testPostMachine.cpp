#include <UnitTest++/UnitTest++.h>
#include <sstream>
#include "PostMachine.hpp"

namespace test
{
    std::string makeRule(ALPHABET symbol, int nextCommand, int altNextCommand = -1)
    {
        std::string result(1, static_cast<char>(symbol));
        result += std::to_string(nextCommand);

        if (symbol == ALPHABET::IF)
        {
            result += ';';
            result += std::to_string(altNextCommand);
        }

        return result;
    }

    std::string run(programm &current, bool flog = false)
    {
        std::ostringstream output;
        std::streambuf *oldBuffer = std::cout.rdbuf(output.rdbuf());

        current.performOperations(flog);

        std::cout.rdbuf(oldBuffer);
        return output.str();
    }
}
TEST(LEFTCOMMANDPROGRAMM)
{
    std::vector<std::string> rules = {
        test::makeRule(ALPHABET::LEFT, 1),
        test::makeRule(ALPHABET::SETMARK, 2),
        test::makeRule(ALPHABET::STOP, 0)};

    programm current("00", rules);

    CHECK_EQUAL(std::string("10\n"), test::run(current));
}

TEST(RIGHTCOMMANDPROGRAMM)
{
    std::vector<std::string> rules = {
        test::makeRule(ALPHABET::RIGHT, 1),
        test::makeRule(ALPHABET::SETMARK, 2),
        test::makeRule(ALPHABET::STOP, 0)};

    programm current("00", rules);

    CHECK_EQUAL(std::string("01\n"), test::run(current));
}

TEST(RIGHTBOUNDARYPROGRAMM)
{
    std::vector<std::string> rules = {
        test::makeRule(ALPHABET::RIGHT, 1),
        test::makeRule(ALPHABET::SETMARK, 2),
        test::makeRule(ALPHABET::STOP, 0)};

    programm current("0", rules);

    CHECK_EQUAL(std::string("1\n"), test::run(current));
}

TEST(SETMARKPROGRAMM)
{
    std::vector<std::string> rules = {
        test::makeRule(ALPHABET::SETMARK, 1),
        test::makeRule(ALPHABET::STOP, 0)};

    programm current("0", rules);

    CHECK_EQUAL(std::string("1\n"), test::run(current));
}

TEST(REMOVEMARKPROGRAMM)
{
    std::vector<std::string> rules = {
        test::makeRule(ALPHABET::REMOVEMARK, 1),
        test::makeRule(ALPHABET::STOP, 0)};

    programm current("1", rules);

    CHECK_EQUAL(std::string("0\n"), test::run(current));
}

TEST(IFZEROEVALUATIONPROGRAMM)
{
    std::vector<std::string> rules = {
        test::makeRule(ALPHABET::IF, 1, 2),
        test::makeRule(ALPHABET::SETMARK, 3),
        test::makeRule(ALPHABET::STOP, 0),
        test::makeRule(ALPHABET::STOP, 0)};

    programm current("0", rules);

    CHECK_EQUAL(std::string("1\n"), test::run(current));
}

TEST(IFONEEVALUATIONPROGRAMM)
{
    std::vector<std::string> rules = {
        test::makeRule(ALPHABET::IF, 1, 2),
        test::makeRule(ALPHABET::STOP, 0),
        test::makeRule(ALPHABET::REMOVEMARK, 3),
        test::makeRule(ALPHABET::STOP, 0)};

    programm current("1", rules);

    CHECK_EQUAL(std::string("0\n"), test::run(current));
}

TEST(STOPCOMMANDPROGRAMM)
{
    std::vector<std::string> rules = {
        test::makeRule(ALPHABET::STOP, 0)};

    programm current("000", rules);

    CHECK_EQUAL(std::string("000\n"), test::run(current));
}

TEST(EMPTYPROGRAMM)
{
    std::vector<std::string> rules;
    programm current("", rules);

    CHECK(current.empty());
}

TEST(NONEMPTYPROGRAMMWITHOUTRULES)
{
    std::vector<std::string> rules;
    programm current("0", rules);

    CHECK(!current.empty());
}

TEST(APPENDSTRINGPROGRAMM)
{
    std::vector<std::string> rules = {
        test::makeRule(ALPHABET::SETMARK, 1)};

    programm current("0", rules);

    current.append(test::makeRule(ALPHABET::STOP, 0));

    CHECK_EQUAL(std::string("1\n"), test::run(current));
}

TEST(APPENDRULEPROGRAMM)
{
    std::vector<std::string> rules = {
        test::makeRule(ALPHABET::SETMARK, 1)};

    programm current("0", rules);

    rule stopRule;
    ALPHABET symbol = ALPHABET::STOP;
    stopRule.setRule(symbol, 0, 0);

    current.append(stopRule);

    CHECK_EQUAL(std::string("1\n"), test::run(current));
}

TEST(REMOVERULEPROGRAMM)
{
    std::vector<std::string> rules = {
        test::makeRule(ALPHABET::RIGHT, 1),
        test::makeRule(ALPHABET::SETMARK, 2),
        test::makeRule(ALPHABET::STOP, 0)};

    programm current("00", rules);

    current.remove(1);

    CHECK_EQUAL(std::string("00\n"), test::run(current));
}

TEST(REMOVEINVALIDRULEPROGRAMM)
{
    std::vector<std::string> rules = {
        test::makeRule(ALPHABET::STOP, 0)};

    programm current("0", rules);

    std::ostringstream output;
    std::streambuf *oldBuffer = std::cout.rdbuf(output.rdbuf());

    current.remove(-1);
    current.remove(100);

    std::cout.rdbuf(oldBuffer);

    CHECK_EQUAL(
        std::string("Rule is not found!\nRule is not found!\n"),
        output.str());
}

TEST(CHANGEFLAGPROGRAMM)
{
    std::vector<std::string> rules;
    programm current("", rules);

    CHECK(!current.getFlog());

    current.changeFlog();
    CHECK(current.getFlog());

    current.changeFlog();
    CHECK(!current.getFlog());
}

TEST(PERFORMOPERATIONSFLAGPROGRAMM)
{
    std::vector<std::string> rules = {
        test::makeRule(ALPHABET::SETMARK, 1),
        test::makeRule(ALPHABET::STOP, 0)};

    programm current("0", rules);

    CHECK_EQUAL(std::string("1\n1\n"), test::run(current, true));
}