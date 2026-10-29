#include "tape.hpp"

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