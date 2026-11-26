#include "cabin.hpp"

cabin::cabin(unsigned int place)
{
    for (int i = 0; i < place; i++)
    {
        this->seat[i] = false;
    }
}

bool cabin::isSeatTaken(const int &seat) const
{
    return this->seat.at(seat) == true;
}

void cabin::setSeat(const int &seat)
{
    this->seat[seat] = true;
}

void cabin::vacateSeat(const int &seat)
{
    this->seat[seat] = false;
}

unsigned int cabin::getAmoutSeat() const
{
    return this->seat.size();
}