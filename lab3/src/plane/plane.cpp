#include "plane.hpp"

plane::plane() = default;

unsigned int plane::getAmoutSeat() const
{
    return this->cabin.getAmoutSeat();
}

void plane::setName(const std::string &name)
{
    this->name = name;
}

void plane::setSeat(const std::set<int> &seat)
{
    for (auto &it : seat)
    {
        this->cabin.setSeat(it);
    }
}

void plane::vacateSeat(const std::set<int> &seat)
{
    for (auto &it : seat)
    {
        this->cabin.vacateSeat(it);
    }
}

STATUSPLANEINSKY plane::getStatusInSky() const
{
    return this->statusInSky;
}

STATUSPLANESTATE plane::getStatusState() const
{
    return this->statusState;
}

void plane::setStatusInSky(STATUSPLANEINSKY status)
{
    this->statusInSky = status;
}

void plane::setStatusState(STATUSPLANESTATE status)
{
    this->statusState = status;
}

void plane::fly()
{
    std::cout << "Самолёт " << this->name << " ЛЕТИТ" << std::endl;
}

void plane::sendMessage()
{
}

void plane::seat()
{
    std::cout << "Самолёт " << this->name << " ПРИЗЕМЛИЛСЯ" << std::endl;
}