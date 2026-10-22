#ifndef POSTMACHINE_HPP

#define POSTMACHINE_HPP
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

enum class ALPHABET
{
    SETMARK = 'V',
    REMOVEMARK = 'X',
    RIGHT = 'R',
    LEFT = 'L',
    IF = '?',
    STOP = '!'
};

class rule
{
private:
    ALPHABET symbol;
    int numberNextCommand = -1;
    int altNumberNextCommand = -1;

public:
    rule() = default;
    rule &operator=(const rule &);

    void setRule(ALPHABET &, const int &, const int &);
    ALPHABET getSymbol() const;
    int getNextCommand() const;
    int getAltNextCommand() const;

    friend std::ostream &operator<<(std::ostream &, const rule &);
};

class tape
{
private:
    std::vector<char> tape_;

public:
    tape() = default;
    tape(std::ifstream &);
    tape(const std::string &);
    tape &operator=(const tape &);

    int size() const;

    void setMark(const int &);
    void removeMark(const int &);

    char &operator[](const int &);

    friend std::ostream &operator<<(std::ostream &, tape &);
    friend std::istream &operator>>(std::istream &, tape &);
};

class programm
{
private:
    bool flog = false;
    std::vector<rule> rule_;
    tape tape_;

    void parser(const std::string &, ALPHABET &, int &, int &);

    void parser(std::vector<std::string> &);
    void parser(std::ifstream &);

    bool step(int &, int &);

public:
    programm() = default;
    programm(std::ifstream &);
    programm(const std::string &, std::vector<std::string> &);
    programm &operator=(const programm &);

    bool getFlog() const;
    bool empty();

    void append(const std::string &);
    void append(const rule &);
    void remove(const int &);
    void viewRule() const;
    void viewTape();

    void changeFlog();

    void performOperations(bool);
};

#endif