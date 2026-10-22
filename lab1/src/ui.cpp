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