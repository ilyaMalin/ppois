#include <UnitTest++/UnitTest++.h>

#define private public
#include "uiMultiset.hpp"
#undef private

namespace test
{
    class UIMultisetTestAccess
    {
    public:
        static bool parser(const UIMultiset &ui, const std::string &expression, std::string &result)
        {
            return ui.parser(expression, result);
        }

        static bool solver(UIMultiset &ui, const std::string &expression, multiset &result)
        {
            return ui.solver(expression, result);
        }

        static void insertSet(UIMultiset &ui, const std::string &name, const multiset &set)
        {
            ui.storage.insert(name, set);
        }

        static void saver(UIMultiset &ui, const multiset &set)
        {
            ui.saver(set);
        }

        static int getPriority(const UIMultiset &ui, const char &operation)
        {
            return ui.getPriorityOperation(operation);
        }
    };
}

TEST(GETPRIORITYUNKNOWNOPERATION)
{
    UIMultiset ui;

    CHECK_EQUAL(-1, test::UIMultisetTestAccess::getPriority(ui, '?'));
}

TEST(SOLVERWITHOUTOPERANDS)
{
    UIMultiset ui;
    multiset result;

    CHECK(!test::UIMultisetTestAccess::solver(ui, "+", result));
}

TEST(SOLVEREMPTYOPERAND)
{
    UIMultiset ui;
    multiset result;

    CHECK(!test::UIMultisetTestAccess::solver(ui, "_", result));
}

TEST(SOLVERWITHOUTDELIMITER)
{
    UIMultiset ui;
    multiset result;

    CHECK(!test::UIMultisetTestAccess::solver(ui, "A", result));
}

TEST(SOLVERMULTIPLEOPERANDS)
{
    UIMultiset ui;
    multiset result;

    test::UIMultisetTestAccess::insertSet(ui, "A", multiset("{a}"));
    test::UIMultisetTestAccess::insertSet(ui, "B", multiset("{b}"));

    CHECK(!test::UIMultisetTestAccess::solver(ui, "A_B_", result));
}

TEST(MENUALLACTIONS)
{
    UIMultiset ui;

    std::istringstream input(
        "1\n" // Создать множество
        "A\n"
        "{a,b}\n"
        "3\n" // Просмотреть множества
        "4\n" // Выполнить операцию
        "A\n"
        "0\n" // Не сохранять результат
        "2\n" // Удалить множество
        "A\n"
        "5\n" // Выход
    );

    std::streambuf *oldCin = std::cin.rdbuf(input.rdbuf());

    std::ostringstream output;
    std::streambuf *oldCout = std::cout.rdbuf(output.rdbuf());

    ui.menu();

    std::cin.rdbuf(oldCin);
    std::cout.rdbuf(oldCout);

    CHECK(output.str().find("Set successfully created!") != std::string::npos);
    CHECK(output.str().find("1. A = ") != std::string::npos);
    CHECK(output.str().find("Result:") != std::string::npos);
    CHECK(output.str().find("Set successfully deleted!") != std::string::npos);
    CHECK(output.str().find("Exit...") != std::string::npos);
}

TEST(MENUINVALIDINPUT)
{
    UIMultiset ui;

    std::istringstream input("abc\n5\n");
    std::streambuf *oldCin = std::cin.rdbuf(input.rdbuf());

    std::ostringstream output;
    std::streambuf *oldCout = std::cout.rdbuf(output.rdbuf());

    ui.menu();

    std::cin.rdbuf(oldCin);
    std::cout.rdbuf(oldCout);

    CHECK(output.str().find("No correct choice!") != std::string::npos);
    CHECK(output.str().find("Exit...") != std::string::npos);
}

TEST(MENUINVALIDINPUTMULTISET)
{
    UIMultiset ui;

    std::istringstream input("abc\n5\n");

    auto oldCinState = std::cin.rdstate();
    std::streambuf *oldCin = std::cin.rdbuf(input.rdbuf());
    std::cin.clear();

    std::ostringstream output;
    std::streambuf *oldCout = std::cout.rdbuf(output.rdbuf());

    ui.menu();

    std::cin.rdbuf(oldCin);
    std::cin.clear(oldCinState);
    std::cout.rdbuf(oldCout);

    CHECK(output.str().find("No correct choice!") != std::string::npos);
    CHECK(output.str().find("Exit...") != std::string::npos);
}

TEST(PARSERMULTIPLICATION)
{
    UIMultiset ui;
    std::string result;

    CHECK(test::UIMultisetTestAccess::parser(ui, "A*B", result));
    CHECK_EQUAL(std::string("A_B_*"), result);
}

TEST(PARSERSUBTRACTION)
{
    UIMultiset ui;
    std::string result;

    CHECK(test::UIMultisetTestAccess::parser(ui, "A-B", result));
    CHECK_EQUAL(std::string("A_B_-"), result);
}

TEST(PARSEROPERATORPRECEDENCE)
{
    UIMultiset ui;
    std::string result;

    CHECK(test::UIMultisetTestAccess::parser(ui, "A+B*C", result));
    CHECK_EQUAL(std::string("A_B_C_*+"), result);
}

TEST(PARSERPARENTHESES)
{
    UIMultiset ui;
    std::string result;

    CHECK(test::UIMultisetTestAccess::parser(ui, "(A+B)*C", result));
    CHECK_EQUAL(std::string("A_B_+C_*"), result);
}

TEST(PARSERNESTEDPARENTHESES)
{
    UIMultiset ui;
    std::string result;

    CHECK(test::UIMultisetTestAccess::parser(ui, "A*(B+C)-D", result));
    CHECK_EQUAL(std::string("A_B_C_+*D_-"), result);
}

TEST(PARSERLEFTASSOCIATIVITY)
{
    UIMultiset ui;
    std::string result;

    CHECK(test::UIMultisetTestAccess::parser(ui, "A-B-C", result));
    CHECK_EQUAL(std::string("A_B_-C_-"), result);
}

TEST(SOLVERADDITION)
{
    UIMultiset ui;

    test::UIMultisetTestAccess::insertSet(ui, "A", multiset("{a,a,b}"));
    test::UIMultisetTestAccess::insertSet(ui, "B", multiset("{a,c}"));

    multiset result;

    CHECK(test::UIMultisetTestAccess::solver(ui, "A_B_+", result));
    CHECK(result == multiset("{a,a,b,c}"));
}

TEST(SOLVERMULTIPLICATION)
{
    UIMultiset ui;

    test::UIMultisetTestAccess::insertSet(ui, "A", multiset("{a,a,b}"));
    test::UIMultisetTestAccess::insertSet(ui, "B", multiset("{a,c}"));

    multiset result;

    CHECK(test::UIMultisetTestAccess::solver(ui, "A_B_*", result));
    CHECK(result == multiset("{a}"));
}

TEST(SOLVERSUBTRACTION)
{
    UIMultiset ui;

    test::UIMultisetTestAccess::insertSet(ui, "A", multiset("{a,a,b}"));
    test::UIMultisetTestAccess::insertSet(ui, "B", multiset("{a,c}"));

    multiset result;

    CHECK(test::UIMultisetTestAccess::solver(ui, "A_B_-", result));
    CHECK(result == multiset("{a,b}"));
}

TEST(CREATEMULTISET)
{
    UIMultiset ui;

    std::istringstream input("A {a,a,b}");
    std::streambuf *oldCin = std::cin.rdbuf(input.rdbuf());

    std::ostringstream output;
    std::streambuf *oldCout = std::cout.rdbuf(output.rdbuf());

    ui.createMultiset(nullptr);

    std::cin.rdbuf(oldCin);
    std::cout.rdbuf(oldCout);

    multiset result;

    CHECK(test::UIMultisetTestAccess::solver(ui, "A_", result));
    CHECK(result == multiset("{a,a,b}"));
    CHECK(output.str().find("Set successfully created!") != std::string::npos);
}

TEST(CREATEMULTISETDUPLICATE)
{
    UIMultiset ui;

    test::UIMultisetTestAccess::insertSet(ui, "A", multiset("{a}"));

    std::istringstream input("A {b}");
    std::streambuf *oldCin = std::cin.rdbuf(input.rdbuf());

    std::ostringstream output;
    std::streambuf *oldCout = std::cout.rdbuf(output.rdbuf());

    ui.createMultiset(nullptr);

    std::cin.rdbuf(oldCin);
    std::cout.rdbuf(oldCout);

    multiset result;

    CHECK(test::UIMultisetTestAccess::solver(ui, "A_", result));
    CHECK(result == multiset("{a}"));
    CHECK(output.str().find("already taken!") != std::string::npos);
}

TEST(SAVERWITHOUTSAVE)
{
    UIMultiset ui;
    multiset result("{a,a,b}");

    std::istringstream input("0");
    std::streambuf *oldCin = std::cin.rdbuf(input.rdbuf());

    std::ostringstream output;
    std::streambuf *oldCout = std::cout.rdbuf(output.rdbuf());

    test::UIMultisetTestAccess::saver(ui, result);

    std::cin.rdbuf(oldCin);
    std::cout.rdbuf(oldCout);

    CHECK(output.str().find("The set is not saved!") != std::string::npos);
    CHECK(output.str().find("Result:") != std::string::npos);
}

TEST(SAVERWITHSAVE)
{
    UIMultiset ui;
    multiset result("{a,a,b}");

    std::istringstream input("1 SavedSet");
    std::streambuf *oldCin = std::cin.rdbuf(input.rdbuf());

    std::ostringstream output;
    std::streambuf *oldCout = std::cout.rdbuf(output.rdbuf());

    test::UIMultisetTestAccess::saver(ui, result);

    std::cin.rdbuf(oldCin);
    std::cout.rdbuf(oldCout);

    multiset savedSet;

    CHECK(test::UIMultisetTestAccess::solver(ui, "SavedSet_", savedSet));
    CHECK(savedSet == result);
}

TEST(DESTRUCTMULTISET)
{
    UIMultiset ui;

    test::UIMultisetTestAccess::insertSet(ui, "A", multiset("{a,b}"));

    std::istringstream input("A");
    std::streambuf *oldCin = std::cin.rdbuf(input.rdbuf());

    std::ostringstream output;
    std::streambuf *oldCout = std::cout.rdbuf(output.rdbuf());

    ui.destructMultiset();

    std::cin.rdbuf(oldCin);
    std::cout.rdbuf(oldCout);

    CHECK(output.str().find("Set successfully deleted!") != std::string::npos);

    std::ostringstream viewOutput;
    oldCout = std::cout.rdbuf(viewOutput.rdbuf());

    ui.viewMultiset();

    std::cout.rdbuf(oldCout);

    CHECK_EQUAL(std::string("Empty!\n"), viewOutput.str());
}

TEST(DESTRUCTMISSINGMULTISET)
{
    UIMultiset ui;

    std::istringstream input("Unknown");
    std::streambuf *oldCin = std::cin.rdbuf(input.rdbuf());

    std::ostringstream output;
    std::streambuf *oldCout = std::cout.rdbuf(output.rdbuf());

    ui.destructMultiset();

    std::cin.rdbuf(oldCin);
    std::cout.rdbuf(oldCout);

    CHECK(output.str().find("is not found!") != std::string::npos);
}

TEST(VIEWEMPTYMULTISET)
{
    UIMultiset ui;

    std::ostringstream output;
    std::streambuf *oldCout = std::cout.rdbuf(output.rdbuf());

    ui.viewMultiset();

    std::cout.rdbuf(oldCout);

    CHECK_EQUAL(std::string("Empty!\n"), output.str());
}

TEST(VIEWMULTISET)
{
    UIMultiset ui;

    test::UIMultisetTestAccess::insertSet(ui, "A", multiset("{a,b}"));
    test::UIMultisetTestAccess::insertSet(ui, "B", multiset("{c,c}"));

    std::ostringstream output;
    std::streambuf *oldCout = std::cout.rdbuf(output.rdbuf());

    ui.viewMultiset();

    std::cout.rdbuf(oldCout);

    CHECK(output.str().find("1. A = ") != std::string::npos);
    CHECK(output.str().find("2. B = ") != std::string::npos);
}

TEST(PERFORMOPERATION)
{
    UIMultiset ui;

    test::UIMultisetTestAccess::insertSet(ui, "A", multiset("{a,a,b}"));
    test::UIMultisetTestAccess::insertSet(ui, "B", multiset("{a,c}"));

    std::istringstream input("A+B 0");
    std::streambuf *oldCin = std::cin.rdbuf(input.rdbuf());

    std::ostringstream output;
    std::streambuf *oldCout = std::cout.rdbuf(output.rdbuf());

    ui.performOperation();

    std::cin.rdbuf(oldCin);
    std::cout.rdbuf(oldCout);

    CHECK(output.str().find("Result:") != std::string::npos);
    CHECK(output.str().find("The set is not saved!") != std::string::npos);
}

TEST(PERFORMOPERATIONUNKNOWNSET)
{
    UIMultiset ui;

    std::istringstream input("Unknown");
    std::streambuf *oldCin = std::cin.rdbuf(input.rdbuf());

    std::ostringstream output;
    std::streambuf *oldCout = std::cout.rdbuf(output.rdbuf());

    ui.performOperation();

    std::cin.rdbuf(oldCin);
    std::cout.rdbuf(oldCout);

    CHECK(output.str().find("Set with name Unknown is not found!") != std::string::npos);
    CHECK(output.str().find("Found a no-know set!") != std::string::npos);
}

TEST(MENUNVALIDCHOICE)
{
    UIMultiset ui;

    std::istringstream input("99\n5\n");
    std::streambuf *oldCin = std::cin.rdbuf(input.rdbuf());

    std::ostringstream output;
    std::streambuf *oldCout = std::cout.rdbuf(output.rdbuf());

    ui.menu();

    std::cin.rdbuf(oldCin);
    std::cout.rdbuf(oldCout);

    CHECK(output.str().find("No correct choice!") != std::string::npos);
}

TEST(PARSER_HIGHER_PRIORITY_POP)
{
    UIMultiset ui;
    std::string result;

    CHECK(test::UIMultisetTestAccess::parser(ui, "A*B+C", result));
    CHECK_EQUAL(std::string("A_B_*C_+"), result);
}

TEST(PARSER_LOWER_PRIORITY_NO_POP)
{
    UIMultiset ui;
    std::string result;

    CHECK(test::UIMultisetTestAccess::parser(ui, "A-B+C", result));
    CHECK_EQUAL(std::string("A_B_C_+-"), result);
}