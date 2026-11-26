#ifndef PLANE_HPP

#define PLANE_HPP
#include <string>
#include "cabin.hpp"
#include "cockpit.hpp"
#include "enum.hpp"
#include <set>
#include <iostream>

class plane
{
private:
    std::string name;
    cabin cabin;
    cockpit cockpit;

    STATUSPLANEINSKY statusInSky = STATUSPLANEINSKY::WAIT;
    STATUSPLANESTATE statusState = STATUSPLANESTATE::ALLGOOD;

public:
    plane();
    unsigned int getAmoutSeat() const;
    void setName(const std::string &);
    void setSeat(const std::set<int> &);
    void vacateSeat(const std::set<int> &);
    STATUSPLANEINSKY getStatusInSky() const;
    STATUSPLANESTATE getStatusState() const;
    void setStatusInSky(STATUSPLANEINSKY);
    void setStatusState(STATUSPLANESTATE);

    void fly();
    void sendMessage();
    void seat();
};

#endif