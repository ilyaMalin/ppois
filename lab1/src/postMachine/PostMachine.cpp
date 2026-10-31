#include "PostMachine.hpp"

void programm::parser(const std::string &ruleString, ALPHABET &symbol, int &nextCommand, int &altNextCommand)
{
    size_t i = 0;
    symbol = static_cast<ALPHABET>(ruleString[i++]);

    while (i < ruleString.size() && std::isdigit(ruleString[i]) && ruleString[i] != ';')
    {
        nextCommand = 10 * nextCommand + ruleString[i] - '0';
        i++;
    }

    if (symbol == ALPHABET::IF)
    {
        if (ruleString[i] != ';')
        {
            throw std::runtime_error("Invalid rule!\n");
        }

        i++;

        while (i < ruleString.size() && std::isdigit(ruleString[i]) && ruleString[i] != ';')
        {
            altNextCommand = 10 * altNextCommand + ruleString[i] - '0';
            i++;
        }
    }
    else
    {
        altNextCommand = -1;
    }
}

void programm::parser(std::ifstream &file)
{
    std::string lineRule;
    while (std::getline(file, lineRule))
    {
        ALPHABET symbol;
        int nextCommand = 0, altNextCommand = 0;
        this->parser(lineRule, symbol, nextCommand, altNextCommand);

        rule tempRule;
        tempRule.setRule(symbol, nextCommand, altNextCommand);

        this->rule_.push_back(tempRule);
    }
}

void programm::parser(const std::vector<std::string> &tapeString)
{
    for (const auto &currentRule : tapeString)
    {
        ALPHABET symbol;
        int nextCommand = 0, altNextCommand = 0;
        this->parser(currentRule, symbol, nextCommand, altNextCommand);

        rule rule;
        rule.setRule(symbol, nextCommand, altNextCommand);

        this->append(rule);
    }
}

programm::programm(const std::string &tapeString, const std::vector<std::string> &ruleString) : tape_(tapeString)
{
    this->parser(ruleString);
}

programm::programm(std::ifstream &file) : tape_(file)
{
    this->parser(file);
}

programm &programm::operator=(const programm &otherProgramm)
{
    this->rule_ = otherProgramm.rule_;
    this->tape_ = otherProgramm.tape_;

    return *this;
}

bool programm::getFlog() const
{
    return this->flog;
}

bool programm::empty()
{
    return this->rule_.empty() && this->tape_.size() == 0;
}

void programm::append(const std::string &ruleString)
{
    ALPHABET symbol;
    int nextCommand = 0, altNextCommand = 0;
    this->parser(ruleString, symbol, nextCommand, altNextCommand);
    rule rule;
    rule.setRule(symbol, nextCommand, altNextCommand);

    this->rule_.push_back(rule);
}

void programm::append(const rule &rule)
{
    this->rule_.push_back(rule);
}

void programm::remove(const int &index)
{
    if (index >= static_cast<int>(this->rule_.size()) || index < 0)
    {
        std::cout << "Rule is not found!\n";
        return;
    }

    auto iterator = this->rule_.begin() + index;
    this->rule_.erase(iterator);
}

void programm::viewRule() const
{
    if (this->rule_.size() == 0)
    {
        std::cout << "List of rules is empty" << std::endl;
        return;
    }

    for (size_t i = 0; i < this->rule_.size(); i++)
    {
        std::cout << this->rule_[i] << std::endl;
    }
}

void programm::viewTape()
{
    if (this->tape_.size() == 0)
    {
        std::cout << "Tape is empty" << std::endl;
        return;
    }

    std::cout << this->tape_ << std::endl;
}

bool programm::step(int &nextCommand, int &carriage)
{
    int currentRule = nextCommand;
    ALPHABET symbol = this->rule_[currentRule].getSymbol();

    switch (symbol)
    {
    case ALPHABET::LEFT:
    {
        if (carriage != 0)
        {
            carriage--;
        }
        break;
    }
    case ALPHABET::RIGHT:
    {
        if (carriage + 1 < this->tape_.size())
        {
            carriage++;
        }
        break;
    }
    case ALPHABET::SETMARK:
    {
        this->tape_[carriage] = '1';
        break;
    }
    case ALPHABET::REMOVEMARK:
    {
        this->tape_[carriage] = '0';
        break;
    }
    case ALPHABET::IF:
    {
        if (this->tape_[carriage] == '0')
        {
            nextCommand = this->rule_[currentRule].getNextCommand();
        }
        else
        {
            nextCommand = this->rule_[currentRule].getAltNextCommand();
        }

        break;
    }
    case ALPHABET::STOP:
    {
        return false;
    }
    }

    if (this->rule_[currentRule].getAltNextCommand() == -1)
    {
        nextCommand = this->rule_[currentRule].getNextCommand();
    }

    return true;
}

void programm::performOperations(bool showLog)
{
    int carriage = 0;
    int nextCommand = 0;
    while (this->step(nextCommand, carriage))
    {
        if (showLog)
        {
            std::cout << this->tape_ << std::endl;
        }
    }

    std::cout << this->tape_ << std::endl;
}

void programm::changeFlog()
{
    this->flog = !this->flog;
}
