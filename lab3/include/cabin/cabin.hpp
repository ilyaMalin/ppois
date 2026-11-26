#ifndef CABIN_HPP

#define CABIN_HPP
#include <map>

class cabin
{
private:
    std::map<int, bool> seat;

public:
    cabin(unsigned int = 100);
    bool isSeatTaken(const int &) const;
    void setSeat(const int &);
    void vacateSeat(const int &);
    unsigned int getAmoutSeat() const;
};

#endif