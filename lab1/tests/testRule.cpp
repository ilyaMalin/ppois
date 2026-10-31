#include <UnitTest++/UnitTest++.h>
#include <sstream>
#include "rule.hpp"

TEST(SETRULE)
{
    rule current;
    ALPHABET symbol{};

    current.setRule(symbol, 3, 5);

    CHECK(current.getSymbol() == symbol);
    CHECK_EQUAL(3, current.getNextCommand());
    CHECK_EQUAL(5, current.getAltNextCommand());
}

TEST(SETRULEWITHOUTALTCOMMAND)
{
    rule current;
    ALPHABET symbol{};

    current.setRule(symbol, 4, -1);

    CHECK_EQUAL(-1, current.getAltNextCommand());
}

TEST(COPYASSIGNMENT)
{
    rule original;
    rule copy;
    ALPHABET symbol{};

    original.setRule(symbol, 3, 7);
    copy.setRule(symbol, 1, 2);

    copy = original;

    CHECK(copy.getSymbol() == original.getSymbol());
    CHECK_EQUAL(original.getNextCommand(), copy.getNextCommand());
    CHECK_EQUAL(original.getAltNextCommand(), copy.getAltNextCommand());
}

TEST(OUTPUTWITHOUTALTCOMMAND)
{
    rule current;
    ALPHABET symbol{};

    current.setRule(symbol, 4, -1);

    std::ostringstream output;
    std::ostringstream expected;

    output << current;
    expected << static_cast<char>(symbol) << 4;

    CHECK_EQUAL(expected.str(), output.str());
}

TEST(OUTPUTWITHALTCOMMAND)
{
    rule current;
    ALPHABET symbol{};

    current.setRule(symbol, 3, 7);

    std::ostringstream output;
    std::ostringstream expected;

    output << current;
    expected << static_cast<char>(symbol) << "3;7";

    CHECK_EQUAL(expected.str(), output.str());
}