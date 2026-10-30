#include <UnitTest++/UnitTest++.h>
#include <sstream>
#include <fstream>

#define private public
#include "uiPost.hpp"
#undef private

namespace test
{
    class UIPostTestAccess
    {
    public:
        static void parser(UIPost &ui, std::string &path)
        {
            ui.parser(path);
        }

        static void loadFile(UIPost &ui, std::ifstream &file)
        {
            ui.loadFile(file);
        }

        static void load(UIPost &ui)
        {
            ui.load();
        }

        static void perform(UIPost &ui)
        {
            ui.perfornProgramm();
        }

        static void menu(UIPost &ui)
        {
            ui.menu();
        }

        static bool getFlog(const UIPost &ui)
        {
            return ui.programm_.getFlog();
        }
    };

    static std::string makeRule(ALPHABET symbol, int nextCommand, int altNextCommand = -1)
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

    template <typename Function>
    std::string captureOutput(Function function)
    {
        std::ostringstream output;
        std::streambuf *oldBuffer = std::cout.rdbuf(output.rdbuf());

        function();

        std::cout.rdbuf(oldBuffer);
        return output.str();
    }
}

TEST(PARSEREMPTYUIPOST)
{
    UIPost current;
    std::string path;

    CHECK_THROW(test::UIPostTestAccess::parser(current, path), std::runtime_error);
}

TEST(PARSERWITHOUTLOGUIPOST)
{
    UIPost current;
    std::string path = "program.txt";

    test::UIPostTestAccess::parser(current, path);

    CHECK_EQUAL(std::string("program.txt"), path);
    CHECK(!test::UIPostTestAccess::getFlog(current));
}

TEST(PARSERWITHLOGUIPOST)
{
    UIPost current;
    std::string path = "program.txt -log";

    test::UIPostTestAccess::parser(current, path);

    CHECK_EQUAL(std::string("program.txt"), path);
    CHECK(test::UIPostTestAccess::getFlog(current));
}

TEST(PARSERTOGGLELOGUIPOST)
{
    UIPost current;
    std::string firstPath = "program.txt -log";
    std::string secondPath = "other.txt -log";

    test::UIPostTestAccess::parser(current, firstPath);
    test::UIPostTestAccess::parser(current, secondPath);

    CHECK(!test::UIPostTestAccess::getFlog(current));
}

TEST(LOADFILEUIPOST)
{
    const std::string path = "test_post_program.txt";

    {
        std::ofstream output(path);
        output << "0\n";
        output << test::makeRule(ALPHABET::SETMARK, 1) << '\n';
        output << test::makeRule(ALPHABET::STOP, 0) << '\n';
    }

    UIPost current;
    std::ifstream input(path);

    test::UIPostTestAccess::loadFile(current, input);

    input.close();
    std::remove(path.c_str());

    std::string result = test::captureOutput([&]()
                                             { test::UIPostTestAccess::perform(current); });

    CHECK_EQUAL(std::string("1\n"), result);
}

TEST(LOADEMPTYFILEUIPOST)
{
    const std::string path = "test_post_empty.txt";

    {
        std::ofstream output(path);
    }

    UIPost current;
    std::ifstream input(path);

    CHECK_THROW(
        test::UIPostTestAccess::loadFile(current, input),
        std::runtime_error);

    input.close();
    std::remove(path.c_str());
}

TEST(PERFORMEMPTYPROGRAMMUIPOST)
{
    UIPost current;

    std::string result = test::captureOutput([&]()
                                             { test::UIPostTestAccess::perform(current); });

    CHECK_EQUAL(std::string("Programm is not taken!\n"), result);
}

TEST(LOADVALIDPROGRAMMUIPOST)
{
    UIPost current;

    std::string inputString =
        "0\n" +
        test::makeRule(ALPHABET::SETMARK, 1) + "\n0\n" +
        test::makeRule(ALPHABET::STOP, 0) + "\n1\n";

    std::istringstream input(inputString);
    std::streambuf *oldBuffer = std::cin.rdbuf(input.rdbuf());

    test::captureOutput([&]()
                        { test::UIPostTestAccess::load(current); });

    std::cin.rdbuf(oldBuffer);

    std::string result = test::captureOutput([&]()
                                             { test::UIPostTestAccess::perform(current); });

    CHECK_EQUAL(std::string("1\n"), result);
}

TEST(LOADINVALIDTAPEUIPOST)
{
    UIPost current;

    std::istringstream input("012\n");
    std::streambuf *oldBuffer = std::cin.rdbuf(input.rdbuf());

    std::string output = test::captureOutput([&]()
                                             { test::UIPostTestAccess::load(current); });

    std::cin.rdbuf(oldBuffer);

    CHECK(output.find("Invalid tape!") != std::string::npos);
}

TEST(MENUINVALIDINPUTUIPOST)
{
    UIPost current;

    std::istringstream input("abc\n8\n");
    std::streambuf *oldCin = std::cin.rdbuf(input.rdbuf());

    std::ostringstream output;
    std::streambuf *oldCout = std::cout.rdbuf(output.rdbuf());

    current.menu();

    std::cin.rdbuf(oldCin);
    std::cout.rdbuf(oldCout);

    CHECK(output.str().find("No correct choice!") != std::string::npos);
    CHECK(output.str().find("Exit...") != std::string::npos);
}

TEST(MENUUNKNOWNCHOICEUIPOST)
{
    UIPost current;

    std::istringstream input("99\n8\n");
    std::streambuf *oldCin = std::cin.rdbuf(input.rdbuf());

    std::ostringstream output;
    std::streambuf *oldCout = std::cout.rdbuf(output.rdbuf());

    current.menu();

    std::cin.rdbuf(oldCin);
    std::cout.rdbuf(oldCout);

    CHECK(output.str().find("No correct choice!") != std::string::npos);
}

TEST(MENULOADINVALIDFILEUIPOST)
{
    UIPost current;

    std::istringstream input(
        "1\n"
        "nonexistent_test_program_file.txt\n"
        "8\n");

    std::streambuf *oldCin = std::cin.rdbuf(input.rdbuf());

    std::ostringstream output;
    std::streambuf *oldCout = std::cout.rdbuf(output.rdbuf());

    current.menu();

    std::cin.rdbuf(oldCin);
    std::cout.rdbuf(oldCout);

    CHECK(output.str().find("WARNING: File can't be load!") != std::string::npos);
    CHECK(output.str().find("Exit...") != std::string::npos);
}

TEST(MENULOADVALIDFILEUIPOST)
{
    const std::string path = "test_uipost_program.txt";
    const std::string stopRule =
        std::string(1, static_cast<char>(ALPHABET::STOP)) + "0";

    {
        std::ofstream file(path);
        file << "0\n";
        file << stopRule << '\n';
    }

    UIPost current;

    std::istringstream input(
        "1\n" + path + "\n"
                       "4\n"
                       "5\n"
                       "3\n"
                       "8\n");

    std::streambuf *oldCin = std::cin.rdbuf(input.rdbuf());

    std::ostringstream output;
    std::streambuf *oldCout = std::cout.rdbuf(output.rdbuf());

    current.menu();

    std::cin.rdbuf(oldCin);
    std::cout.rdbuf(oldCout);

    input.clear();
    std::remove(path.c_str());

    CHECK(output.str().find(stopRule) != std::string::npos);
    CHECK(output.str().find("Exit...") != std::string::npos);
}

TEST(MENUREMOVEINVALIDINDEXUIPOST)
{
    UIPost current;

    std::istringstream input("7\nabc\n");
    std::streambuf *oldCin = std::cin.rdbuf(input.rdbuf());

    std::ostringstream output;
    std::streambuf *oldCout = std::cout.rdbuf(output.rdbuf());

    current.menu();

    std::cin.rdbuf(oldCin);
    std::cout.rdbuf(oldCout);

    CHECK(output.str().find("Invalid index!") != std::string::npos);
}