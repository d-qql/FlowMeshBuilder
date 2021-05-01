//
// Created by d-qql on 28.04.2021.
//

#ifndef FLOWMESHBUILDER_MESH_H
#define FLOWMESHBUILDER_MESH_H

#include "Cell.h"
#include <fstream>
#include <unordered_map>

class Mesh {
    using idx_t = unsigned int;
public:

    std::unordered_map<idx_t, Node> Nodes;
    std::unordered_map<idx_t, Triangle> Triangles;
    std::unordered_map<idx_t, Cell> InternalCells;
    std::unordered_map<idx_t, Cell> InternalBoundaryCells;
    std::unordered_map<idx_t, Cell> ExternalBoundaryCells;

    explicit Mesh(std::ifstream& UNVmesh);
};


#endif //FLOWMESHBUILDER_MESH_H
