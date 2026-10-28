#include "ui.hpp"

int UI::getPriorityOperation(const char &operation) const
{
    switch (operation)
    {
    case '*':
        return 2;
    case '+':
        return 1;
    case '-':
        return 0;
    }

    return -1;
}

bool UI::parser(const std::string &expression, std::string &processedExpression) const
{
    std::stack<char> operation;
    std::map<char, bool> listOperation = {{'+', true}, {'*', true}, {'-', true}, {'(', true}, {')', true}};

    size_t i = 0;
    while (i < expression.size())
    {
        if (expression[i] == '(')
        {
            operation.push(expression[i++]);
        }
        else if (expression[i] == ')')
        {
            while (operation.top() != '(')
            {
                processedExpression += operation.top();
                operation.pop();
            }

            operation.pop();
            i++;
        }
        else if (listOperation.contains(expression[i]))
        {
            int priorityCurrentOperation = getPriorityOperation(expression[i]);
            while (!operation.empty() && operation.top() != '(' &&
                   getPriorityOperation(operation.top()) >= priorityCurrentOperation)
            {
                processedExpression += operation.top();
                operation.pop();
            }

            operation.push(expression[i]);
            ++i;
        }
        else
        {
            while (i < expression.size() && !listOperation.contains(expression[i]))
            {
                processedExpression += expression[i++];
            }

            processedExpression += '_';
        }
    }

    while (!operation.empty())
    {
        processedExpression += operation.top();
        operation.pop();
    }

    return true;
}

bool UI::solver(const std::string &processedExpression, multiset &newSet)
{
    std::stack<multiset> operand;
    std::map<char, bool> listOperation = {{'+', true}, {'*', true}, {'-', true}};

    size_t i = 0;
    while (i < processedExpression.size())
    {
        if (listOperation.contains(processedExpression[i]))
        {
            if (operand.size() < 2)
            {
                return false;
            }

            multiset operand_1 = operand.top();
            operand.pop();
            multiset operand_2 = operand.top();
            operand.pop();

            multiset preResult;
            switch (processedExpression[i])
            {
            case '+':
                preResult = operand_2 + operand_1;
                break;

            case '*':
                preResult = operand_2 * operand_1;
                break;

            case '-':
                preResult = operand_2 - operand_1;
                break;
            }

            operand.push(preResult);
            i++;
        }
        else
        {
            std::string operandString;
            while (i < processedExpression.size() && processedExpression[i] != '_')
            {
                operandString += processedExpression[i];
                i++;
            }

            if (operandString.empty() || i == processedExpression.size())
            {
                return false;
            }

            i++;
            operand.push(this->storage[operandString]);
        }
    }

    if (operand.size() != 1)
    {
        return false;
    }

    newSet = operand.top();

    return true;
}

void UI::saver(const multiset &set)
{
    std::cout << "Save a result? (1 - yes, any - no): ";
    unsigned choice;
    std::cin >> choice;

    if (choice == 1)
    {
        this->createMultiset(&set);
    }
    else
    {
        std::cout << "Result: " << set << std::endl;
        std::cout << "The set is not saved!\n";
    }
}

void UI::createMultiset(const multiset *fromSaver = nullptr)
{
    std::cout << "WARNING: Don't use '_' and digits in name of set. And also enter elements like '{a,f,{fa}}!'!\nName a new set: ";
    std::string nameSet;
    std::cin >> nameSet;

    multiset newSet;

    if (!fromSaver)
    {
        std::cout << "Elements of the set: ";
        std::string element;
        std::cin >> element;
        newSet = multiset(element);
    }
    else
    {
        newSet = *fromSaver;
    }

    if (!storage.insert(nameSet, newSet))
    {
        std::cout << "A set with this name is already taken!" << std::endl;
    }
    else
    {
        std::cout << "Set successfully created!" << std::endl;
    }
}

void UI::destructMultiset()
{
    std::cout << "Name of the set to delete: ";
    std::string nameSet;
    std::cin >> nameSet;

    if (!this->storage.remove(nameSet))
    {
        std::cout << "A set with this name is not found!" << std::endl;
    }
    else
    {
        std::cout << "Set successfully deleted!" << std::endl;
    }
}

void UI::viewMultiset()
{
    if (this->storage.empty())
    {
        std::cout << "Empty!" << std::endl;
        return;
    }

    size_t numberSet = 1;
    for (const auto &iterator : this->storage)
    {
        std::cout << numberSet++ << ". " << iterator.first << " = " << iterator.second << std::endl;
    }
}

void UI::performOperation()
{
    std::cout << "Enter a expression: ";
    std::string expression;
    std::cin >> expression;

    std::string processedExpression;
    if (this->parser(expression, processedExpression))
    {
        multiset newSet;

        if (this->solver(processedExpression, newSet))
        {
            this->saver(newSet);
        }
        else
        {
            std::cout << "Found a no-know set!\n";
        }
    }
    else
    {
        std::cout << "No correct expression!\n";
    }
}

void UI::menu()
{
    unsigned choice;

    do
    {
        std::cout << "Main menu" << std::endl
                  << "1. Create a set" << std::endl
                  << "2. Delete a set" << std::endl
                  << "3. View sets" << std::endl
                  << "4. Perform operation" << std::endl
                  << "5. Exit" << std::endl
                  << "Choose action: ";

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
            createMultiset();
            break;
        case 2:
            destructMultiset();
            break;
        case 3:
            viewMultiset();
            break;
        case 4:
            performOperation();
            break;
        case 5:
            std::cout << "Exit..." << std::endl;
            return;
        default:
            std::cout << "No correct choice!" << std::endl;
        }
    } while (choice != 5);
}

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
            std::cout << "Enter absolute path to file.txt: ";
            std::string path;
            std::getline(std::cin, path);

            this->parser(path);

            std::ifstream file(path);
            this->loadFile(file);
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
