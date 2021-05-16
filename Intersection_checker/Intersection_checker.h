#ifndef FLOWMESHBUILDER_INTERSECTION_CKECKER_H
#define FLOWMESHBUILDER_INTERSECTION_CKECKER_H

#include "../Mesh/Mesh.h"

using idx_t = unsigned int;

idx_t findIntersection(const Node& node1, const Node& node2, idx_t cellIndex, const Mesh& mesh);


#endif //FLOWMESHBUILDER_INTERSECTION_CKECKER_H
