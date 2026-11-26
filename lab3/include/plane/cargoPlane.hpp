#ifndef CARGPLANE_SPP

#define CARGPLANE_SPP
#include "plane.hpp"
#include <vector>

class cargoPlane : public plane
{
private:
    size_t maxVoluem;
    std::vector<std::string> cargo;

    WORKLOAD workload = WORKLOAD::EMPTY;

public:
    cargoPlane(size_t = 100);
    void appendCargo(const std::string &);
    std::vector<std::string> unload();
    WORKLOAD getWorkload() const;
};

#endif