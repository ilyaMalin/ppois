#include "include/multiset.hpp"

// test
int main()
{
    multiset set;

    element elem1;
    std::string s1 = "a";
    elem1.setStringValue("a");

    element elem2;
    std::string s2 = "b";
    elem2.setStringValue(s2);

    element elem3;
    std::string s3 = "a";
    elem3.setStringValue(s3);

    element elem4;
    std::string s4 = "d";
    elem4.setStringValue("d");

    set.insert(elem1);
    set.insert(elem2);
    set.insert(elem3);
    set.insert(elem4);

    std::cout << "good\n";
}