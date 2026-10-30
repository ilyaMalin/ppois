#include <UnitTest++/UnitTest++.h>
#include "storageMultiset.hpp"

TEST(DEFAULTCONSTRUCTORSTORAGEMULTISET)
{
    storageMultiset storage;

    CHECK(storage.empty());
    CHECK(storage.begin() == storage.end());
}

TEST(INSERTSTORAGEMULTISET)
{
    storageMultiset storage;
    multiset set("{a, a, b}");

    CHECK(storage.insert("first", set));
    CHECK(!storage.empty());

    CHECK(storage["first"] == set);
}

TEST(INSERTDUPLICATESTORAGEMULTISET)
{
    storageMultiset storage;

    multiset first("{a, b}");
    multiset second("{c, d}");

    CHECK(storage.insert("set", first));
    CHECK(!storage.insert("set", second));

    CHECK(storage["set"] == first);
}

TEST(REMOVESTORAGEMULTISET)
{
    storageMultiset storage;
    multiset set("{a, b}");

    storage.insert("first", set);

    CHECK(storage.remove("first"));
    CHECK(storage.empty());
}

TEST(REMOVENONEXISTENTSTORAGEMULTISET)
{
    storageMultiset storage;

    CHECK(!storage.remove("unknown"));
    CHECK(storage.empty());
}

TEST(ACCESSEXISTINGSTORAGEMULTISET)
{
    storageMultiset storage;
    multiset expected("{a, a, b}");

    storage.insert("first", expected);

    CHECK(storage["first"] == expected);
}

TEST(ACCESSMODIFICATIONSTORAGEMULTISET)
{
    storageMultiset storage;
    multiset set("{a}");

    storage.insert("first", set);

    element elem;
    elem.setStringValue("b");

    storage["first"].insert(elem);

    CHECK(storage["first"] == multiset("{a, b}"));
}

TEST(ACCESSNONEXISTENTSTORAGEMULTISET)
{
    storageMultiset storage;

    CHECK_THROW(storage["unknown"], std::runtime_error);
}

TEST(ITERATORSSTORAGEMULTISET)
{
    storageMultiset storage;

    multiset first("{a}");
    multiset second("{b}");

    storage.insert("alpha", first);
    storage.insert("beta", second);

    auto iterator = storage.begin();

    CHECK(iterator != storage.end());
    CHECK_EQUAL(std::string("alpha"), iterator->first);
    CHECK(iterator->second == first);

    ++iterator;

    CHECK(iterator != storage.end());
    CHECK_EQUAL(std::string("beta"), iterator->first);
    CHECK(iterator->second == second);

    ++iterator;

    CHECK(iterator == storage.end());
}
