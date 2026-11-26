#include "cargoPlane.hpp"

cargoPlane::cargoPlane(size_t maxVoluem) : maxVoluem(maxVoluem)
{
    this->cargo.reserve(maxVoluem);
}

void cargoPlane::appendCargo(const std::string &cargo)
{
    if (this->cargo.size() < this->maxVoluem)
    {
        this->workload = WORKLOAD::FULL;
        this->cargo.push_back(cargo);
        this->maxVoluem++;
    }
}

std::vector<std::string> cargoPlane::unload()
{
    std::vector<std::string> cargo = this->cargo;
    this->cargo.clear();
    this->workload = WORKLOAD::EMPTY;
    return cargo;
}

WORKLOAD cargoPlane::getWorkload() const
{
    return this->workload;
}