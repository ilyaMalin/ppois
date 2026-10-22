#include "PostMachine.hpp"

rule &rule::operator=(const rule &otherRule)
{
    this->symbol = otherRule.symbol;
    this->numberNextCommand = otherRule.numberNextCommand;
    this->altNumberNextCommand = otherRule.altNumberNextCommand;

    return *this;
}

void rule::setRule(ALPHABET &symbol, const int &nextCommand, const int &altNextCommand = -1)
{
    this->symbol = symbol;
    this->numberNextCommand = nextCommand;
    this->altNumberNextCommand = altNextCommand;
}

ALPHABET rule::getSymbol() const
{
    return this->symbol;
}

int rule::getNextCommand() const
{
    return this->numberNextCommand;
}

int rule::getAltNextCommand() const
{
    return this->altNumberNextCommand;
}

std::ostream &operator<<(std::ostream &os, const rule &rule)
{
    os << static_cast<char>(rule.symbol) << rule.numberNextCommand;

    if (rule.altNumberNextCommand != -1)
    {
        os << ';' << rule.altNumberNextCommand;
    }

    return os;
}

tape::tape(std::ifstream &file)
{
    std::string tapeString;
    if (!std::getline(file, tapeString))
    {
        throw std::runtime_error("File can't be empty!\n");
    }

    this->tape_.clear();

    for (const char &cell : tapeString)
    {
        this->tape_.push_back(cell);
    }
}

tape::tape(const std::string &tapeString)
{
    this->tape_.clear();

    for (const char &cell : tapeString)
    {
        this->tape_.push_back(cell);
    }
}

tape &tape::operator=(const tape &otherTape)
{
    this->tape_ = otherTape.tape_;

    return *this;
}

int tape::size() const
{
    return this->tape_.size();
}

void tape::setMark(const int &index)
{
    this->tape_[index] = '1';
}

void tape::removeMark(const int &index)
{
    this->tape_[index] = '0';
}

char &tape::operator[](const int &index)
{
    return this->tape_[index];
}

std::ostream &operator<<(std::ostream &os, tape &tape)
{
    for (size_t i = 0; i < tape.tape_.size(); i++)
    {
        os << tape[i];
    }

    return os;
}

std::istream &operator>>(std::istream &is, tape &mainTape)
{
    std::string path;
    is >> path;

    tape tempTape(path);
    mainTape = tempTape;

    return is;
}

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

void programm::parser(std::vector<std::string> &tapeString)
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

programm::programm(const std::string &tapeString, std::vector<std::string> &ruleString) : tape_(tapeString)
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
    if (index >= static_cast<int>(this->rule_.size()))
    {
        std::cout << "Rule is not found!\n";
        return;
    }

    auto iterator = this->rule_.begin() + index;
    this->rule_.erase(iterator);
}

void programm::viewRule() const
{
    for (size_t i = 0; i < this->rule_.size(); i++)
    {
        std::cout << this->rule_[i] << std::endl;
    }
}

void programm::viewTape()
{
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

void programm::performOperations(bool flog)
{
    int carriage = 0;
    int nextCommand = 0;
    while (this->step(nextCommand, carriage))
    {
        if (flog)
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
