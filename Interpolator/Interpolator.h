//
// Created by node on 12.05.2021.
//

#ifndef FLOWMESHBUILDER_INTERPOLATOR_H
#define FLOWMESHBUILDER_INTERPOLATOR_H

#include <array>
#include "../Mesh/Node.h"
#include "../Mesh/Mesh.h"

using idx_t = unsigned int;

std::array<double, 3> Interpolator(const Node& node, idx_t cellIndex, const Mesh& mesh);

#endif //FLOWMESHBUILDER_INTERPOLATOR_H
