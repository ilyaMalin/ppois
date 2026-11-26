#include "cockpit.hpp"

void cockpit::setCockpitSeat(int place, bool taken)
{
    if (place == 0)
    {
        this->seat.first = taken;
    }
    else
    {
        this->seat.second = taken;
    }
}