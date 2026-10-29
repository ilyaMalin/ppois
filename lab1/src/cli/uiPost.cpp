#include "uiPost.hpp"

void UIPost::parser(std::string &path)
{
    if (path.empty())
    {
        throw std::runtime_error("Path can't be empty!\n");
    }

    const std::string postffix = " -log";
    int size = path.size();
    const std::string chekerFlog = path.substr(size - 5);

    if (chekerFlog == postffix)
    {
        this->programm_.changeFlog();
        path.erase(size - 5);
    }
}

void UIPost::loadFile(std::ifstream &file)
{
    programm tempProgramm(file);
    this->programm_ = tempProgramm;
}

void UIPost::perfornProgramm()
{
    if (this->programm_.empty())
    {
        std::cout << "Programm is not taken!\n";
        return;
    }

    bool flog = this->programm_.getFlog();
    this->programm_.performOperations(flog);
}

void UIPost::load()
{
    std::cout << "Enter a tape (like '1010101010101010101'):";
    std::string tape;
    std::cin >> tape;

    for (const char &cell : tape)
    {
        if (cell != '1' && cell != '0')
        {
            std::cout << "Invalid tape!\n";
            return;
        }
    }

    std::vector<std::string> listRule;
    while (true)
    {
        std::cout << "Enter a rule (like 'X4', '?41;789'): ";
        std::string rule;
        std::cin >> rule;

        listRule.push_back(rule);

        std::cin.ignore();
        std::cout << "Rule? (0 - yes, 1 - no): ";
        unsigned choice = 0;
        std::cin >> choice;

        if (choice != 0)
        {
            break;
        }

        std::cin.ignore();
    }

    programm tempProgramm(tape, listRule);
    this->programm_ = tempProgramm;
}

void UIPost::menu()
{
    unsigned choice = 0;

    do
    {
        std::cout << "Main menu" << std::endl
                  << "1. Load from file" << std::endl
                  << "2. Load" << std::endl
                  << "3. Start a programm" << std::endl
                  << "4. View rules" << std::endl
                  << "5. View a tape" << std::endl
                  << "6. Append a rule" << std::endl
                  << "7. Remove a rule" << std::endl
                  << "8. Exit" << std::endl
                  << "Choice: ";

        if (!(std::cin >> choice))
        {
            std::cout << "No correct choice!" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (choice)
        {
        case 1:
        {
            std::cin.ignore();
            std::cout << "Enter path to file.txt: ";
            std::string path;

            try
            {
                std::getline(std::cin, path);

                this->parser(path);

                std::ifstream file(path);
                this->loadFile(file);
            }
            catch (const std::exception &)
            {
                std::cout << "WARNING: File can't be load!" << std::endl;
            }

            break;
        }
        case 2:
        {
            this->load();
            break;
        }
        case 3:
        {
            this->perfornProgramm();
            break;
        }
        case 4:
        {
            this->programm_.viewRule();
            break;
        }
        case 5:
        {
            this->programm_.viewTape();
            break;
        }
        case 6:
        {
            std::cout << "Enter a rule (like 'X4', '?41;789'): ";
            std::string ruleString;
            std::cin >> ruleString;

            this->programm_.append(ruleString);
            break;
        }
        case 7:
        {
            std::cout << "Enter a index: ";
            int index = 0;
            if (!(std::cin >> index))
            {
                std::cout << "Invalid index!\n";
                return;
            }

            this->programm_.remove(index);
            break;
        }
        case 8:
            std::cout << "Exit..." << std::endl;
            return;
        default:
            std::cout << "No correct choice!" << std::endl;
        }
    } while (choice != 8);
}
