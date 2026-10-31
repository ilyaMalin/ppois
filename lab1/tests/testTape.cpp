#include <UnitTest++/UnitTest++.h>
#include <sstream>
#include "tape.hpp"

TEST(STRINGCONSTRUCTORTAPE)
{
    tape current("10101");

    CHECK_EQUAL(5, current.size());

    CHECK_EQUAL('1', current[0]);
    CHECK_EQUAL('0', current[1]);
    CHECK_EQUAL('1', current[2]);
    CHECK_EQUAL('0', current[3]);
    CHECK_EQUAL('1', current[4]);
}

TEST(EMPTYSTRINGCONSTRUCTORTAPE)
{
    tape current("");

    CHECK_EQUAL(0, current.size());
}

TEST(FILECONSTRUCTORTAPE)
{
    const std::string path = "test_tape_input.txt";

    {
        std::ofstream output(path);
        output << "10101";
    }

    std::ifstream input(path);
    tape current(input);

    CHECK_EQUAL(5, current.size());
    CHECK_EQUAL('1', current[0]);
    CHECK_EQUAL('0', current[1]);
    CHECK_EQUAL('1', current[2]);

    input.close();
    std::remove(path.c_str());
}

TEST(COPYASSIGNMENTTAPE)
{
    tape original("10101");
    tape copy("000");

    copy = original;

    CHECK_EQUAL(original.size(), copy.size());

    for (int i = 0; i < original.size(); ++i)
    {
        CHECK_EQUAL(original[i], copy[i]);
    }
}

TEST(SETMARKTAPE)
{
    tape current("000");

    current.setMark(1);

    CHECK_EQUAL('1', current[1]);
}

TEST(REMOVEMARKTAPE)
{
    tape current("111");

    current.removeMark(1);

    CHECK_EQUAL('0', current[1]);
}

TEST(INDEXOPERATORTAPE)
{
    tape current("000");

    current[1] = '1';

    CHECK_EQUAL('1', current[1]);
}

TEST(OUTPUTOPERATORTAPE)
{
    tape current("10101");
    std::ostringstream output;

    output << current;

    CHECK_EQUAL(std::string("10101"), output.str());
}

TEST(INPUTOPERATORTAPE)
{
    tape current("000");
    std::istringstream input("10101");

    input >> current;

    CHECK_EQUAL(5, current.size());
    CHECK_EQUAL('1', current[0]);
    CHECK_EQUAL('0', current[1]);
    CHECK_EQUAL('1', current[2]);
    CHECK_EQUAL('0', current[3]);
    CHECK_EQUAL('1', current[4]);
}
