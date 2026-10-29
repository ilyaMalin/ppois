#include "rule.hpp"

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