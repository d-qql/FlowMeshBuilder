#ifndef FLOWMESHBUILDER_LSGM_H
#define FLOWMESHBUILDER_LSGM_H

#include <array>
#include "..Mesh/Mesh.h"
#include "../Mesh/Cell.h"

using idx_t = unsigned int;

std::array<double, 3> LSGradient(Cell &Cell, Mesh $Mesh) {
    std::vector<double> Distances;
    Distances.resize(Cell.neighbours.size())
}

#endif //FLOWMESHBUILDER_LSGM_H
