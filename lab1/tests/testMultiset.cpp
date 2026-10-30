#include <UnitTest++/UnitTest++.h>
#include "multiset.hpp"
#include <initializer_list>
#include <sstream>

namespace
{
    element createElement(const std::string &value)
    {
        element elem;
        elem.setStringValue(value);
        return elem;
    }

    multiset createMultiset(std::initializer_list<std::string> values)
    {
        multiset result;

        for (const auto &value : values)
        {
            result.insert(createElement(value));
        }

        return result;
    }
}

TEST(DEFAULTCONSTRUCTORSET)
{
    multiset set;

    CHECK(set.empty());
    CHECK_EQUAL(0, set.cardinality());
}

TEST(CHARCONSTRUCTORSET)
{
    multiset set("{a, a, b}");

    std::ostringstream stream;
    stream << set;

    CHECK_EQUAL(std::string("{a, a, b}"), stream.str());
}

TEST(STRINGCONSTRUCTORSET)
{
    std::string source = "{a, b, b}";
    multiset set(source);

    CHECK_EQUAL(3, set.cardinality());
    CHECK(set[createElement("a")]);
    CHECK(set[createElement("b")]);
}

TEST(EMPTYSTRINGCONSTRUCTORSET)
{
    multiset set("{}");

    CHECK(set.empty());
    CHECK_EQUAL(0, set.cardinality());
}

TEST(NESTEDMULTIPLICITYCONSTRUCTORSET)
{
    multiset set("{a, {b, c}}");

    multiset nested = createMultiset({"b", "c"});
    element nestedElement;
    nestedElement.setSetValue(nested);

    CHECK_EQUAL(2, set.cardinality());
    CHECK(set[nestedElement]);
}

TEST(ELEMENTCONSTRUCTORSET)
{
    element elem = createElement("a");
    multiset set(elem);

    CHECK_EQUAL(1, set.cardinality());
    CHECK(set[elem]);
}

TEST(COPYCONSTRUCTORSET)
{
    multiset original = createMultiset({"a", "a", "b"});
    multiset copy(original);

    CHECK(original == copy);
    CHECK_EQUAL(original.cardinality(), copy.cardinality());
}

TEST(COPYASSIGNMENTSET)
{
    multiset original = createMultiset({"a", "b"});
    multiset copy = createMultiset({"c", "d", "e"});

    copy = original;

    CHECK(copy == original);
    CHECK_EQUAL(2, copy.cardinality());
}

TEST(SELFASSIGNMENTSET)
{
    multiset set = createMultiset({"a", "b"});

    set = set;

    CHECK_EQUAL(2, set.cardinality());
    CHECK(set == createMultiset({"a", "b"}));
}

TEST(INSERTREMOVESET)
{
    multiset set;
    element a = createElement("a");
    element b = createElement("b");

    set.insert(a);
    set.insert(a);
    set.insert(b);

    CHECK_EQUAL(3, set.cardinality());
    CHECK(set[a]);
    CHECK(set[b]);

    set.remove(a);

    CHECK_EQUAL(2, set.cardinality());
    CHECK(set[a]);

    set.remove(a);

    CHECK_EQUAL(1, set.cardinality());
    CHECK(!set[a]);

    set.remove(a);

    CHECK_EQUAL(1, set.cardinality());
}

TEST(INSERTNESTEDSET)
{
    multiset inner = createMultiset({"a", "b"});
    multiset outer;

    outer.insert(inner);

    element nested;
    nested.setSetValue(inner);

    CHECK_EQUAL(1, outer.cardinality());
    CHECK(outer[nested]);
}

TEST(INDEXOPERATORSET)
{
    multiset set = createMultiset({"a", "b"});

    CHECK(set[createElement("a")]);
    CHECK(set[createElement("b")]);
    CHECK(!set[createElement("c")]);
}

TEST(OUTPUTEMPTYSET)
{
    multiset set;
    std::ostringstream output;

    output << set;

    CHECK_EQUAL(std::string("{}"), output.str());
}

TEST(UNIONSET)
{
    multiset first = createMultiset({"a", "a", "b"});
    multiset second = createMultiset({"a", "b", "b", "c"});

    multiset expected = createMultiset({"a", "a", "b", "b", "c"});

    CHECK(first + second == expected);

    first += second;

    CHECK(first == expected);
    CHECK_EQUAL(5, first.cardinality());
}

TEST(INTERSECTIONSET)
{
    multiset first = createMultiset({"a", "a", "a", "b", "c", "c"});
    multiset second = createMultiset({"a", "b", "b", "d"});

    multiset expected = createMultiset({"a", "b"});

    CHECK(first * second == expected);

    first *= second;

    CHECK(first == expected);
    CHECK_EQUAL(2, first.cardinality());
}

TEST(SUBTRACTIONSET)
{
    multiset first = createMultiset({"a", "a", "a", "b", "c"});
    multiset second = createMultiset({"a", "a", "b", "b", "d"});

    multiset expected = createMultiset({"a", "c"});

    CHECK(first - second == expected);

    first -= second;

    CHECK(first == expected);
    CHECK_EQUAL(2, first.cardinality());
}

TEST(BUILDBOOLEANEMPTYSET)
{
    multiset original;
    multiset boolean = original.buildBoolean();

    multiset emptySubset;
    element nested;
    nested.setSetValue(emptySubset);

    CHECK_EQUAL(1, boolean.cardinality());
    CHECK(boolean[nested]);
}

TEST(BUILDBOOLEANSET)
{
    multiset original = createMultiset({"a", "a", "b"});
    multiset boolean = original.buildBoolean();

    CHECK_EQUAL(6, boolean.cardinality());

    auto containsSubset = [&boolean](const multiset &subset)
    {
        element nested;
        nested.setSetValue(subset);

        return boolean[nested];
    };

    CHECK(containsSubset(createMultiset({})));
    CHECK(containsSubset(createMultiset({"a"})));
    CHECK(containsSubset(createMultiset({"a", "a"})));
    CHECK(containsSubset(createMultiset({"b"})));
    CHECK(containsSubset(createMultiset({"a", "b"})));
    CHECK(containsSubset(createMultiset({"a", "a", "b"})));

    CHECK(!containsSubset(createMultiset({"b", "b"})));
}