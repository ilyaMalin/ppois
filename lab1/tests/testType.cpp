#include <UnitTest++/UnitTest++.h>
#include "multiset.hpp"
#include "type.hpp"
#include <sstream>

TEST(DEFAULTCONSTRUCTOR)
{
    element element;

    CHECK_EQUAL(nullptr, element.getStringValue());
    CHECK_EQUAL(nullptr, element.getSetValue());
}

TEST(COPYCONSTRUCTOR)
{
    element elem1;

    const std::string testString = "testString";
    elem1.setStringValue(testString);

    element elem2 = elem1;
    CHECK_EQUAL(testString, *elem2.getStringValue());
    CHECK_EQUAL(nullptr, elem2.getSetValue());

    multiset multiset("testSet");

    element elem3;
    elem3.setSetValue(multiset);

    CHECK_EQUAL(nullptr, elem3.getStringValue());
    CHECK_EQUAL(multiset, *elem3.getSetValue());
}

TEST(OTHERELEMENTCONSTRUCTOR)
{
    element elem1;

    const std::string testString = "testString";
    elem1.setStringValue(testString);

    element elem2(elem1);
    CHECK_EQUAL(testString, *elem2.getStringValue());
    CHECK_EQUAL(nullptr, elem1.getSetValue());

    multiset multiset("testSet");

    element elem3;
    elem3.setSetValue(multiset);

    element elem4(elem3);
    CHECK_EQUAL(nullptr, elem4.getStringValue());
    CHECK_EQUAL(multiset, *elem4.getSetValue());
}

TEST(EQUALSTRINGELEMENTS)
{
    element elem1;
    element elem2;

    elem1.setStringValue("apple");
    elem2.setStringValue("apple");

    CHECK(elem1 == elem2);
    CHECK(!(elem1 < elem2));
    CHECK(!(elem1 > elem2));
}

TEST(UNEQUALSTRINGELEMENTS)
{
    element elem1;
    element elem2;

    elem1.setStringValue("testString1");
    elem2.setStringValue("testString2");

    CHECK(!(elem1 == elem2));
    CHECK(elem1 < elem2);
    CHECK(elem2 > elem1);
}

TEST(EQUALSETELEMENTS)
{
    multiset set("testSet");

    element elem1;
    element elem2;

    elem1.setSetValue(set);
    elem2.setSetValue(set);

    CHECK(elem1 == elem2);
    CHECK(!(elem1 < elem2));
    CHECK(!(elem1 > elem2));
}

TEST(DIFFERENTELEMENTTYPES)
{
    multiset set("testSet");

    element stringElement;
    element setElement;

    stringElement.setStringValue("testString");
    setElement.setSetValue(set);

    CHECK(!(stringElement == setElement));

    CHECK(setElement < stringElement);
    CHECK(stringElement > setElement);

    CHECK(!(stringElement < setElement));
    CHECK(!(setElement > stringElement));
}

TEST(OUTPUTSTRING)
{
    element elem;
    elem.setStringValue("testString");

    std::ostringstream stream;
    stream << elem;

    CHECK_EQUAL("testString", stream.str());
}

TEST(OUTPUTSET)
{
    multiset set("testSet");

    element elem;
    elem.setSetValue(set);

    std::ostringstream stream;
    stream << elem;

    std::ostringstream expected;
    expected << set;

    CHECK_EQUAL(expected.str(), stream.str());
}

TEST(COPYASSIGNMENTSTRINGELEMENT)
{
    element original;
    original.setStringValue("original");

    element copy;
    copy.setStringValue("copy");

    copy = original;

    CHECK(copy == original);
    CHECK(copy.getStringValue() != nullptr);
    CHECK_EQUAL(std::string("original"), *copy.getStringValue());
}

TEST(COPYASSIGNMENTSETELEMENT)
{
    multiset originalSet("{a,a,b}");
    multiset initialSet("{c}");

    element original;
    original.setSetValue(originalSet);

    element copy;
    copy.setSetValue(initialSet);

    copy = original;

    CHECK(copy == original);
    CHECK(copy.getSetValue() != nullptr);
    CHECK(*copy.getSetValue() == originalSet);
}
