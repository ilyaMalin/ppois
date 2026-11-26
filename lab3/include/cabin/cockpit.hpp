#ifndef COCKPIT

#define COCKPIT
#include <utility>

class cockpit
{
private:
    std::pair<bool, bool> seat;

public:
    void setCockpitSeat(int, bool);
};

#endif