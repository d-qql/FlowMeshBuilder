//
// Created by d-qql on 28.04.2021.
//

#ifndef FLOWMESHBUILDER_MESH_H
#define FLOWMESHBUILDER_MESH_H

#include "Cell.h"
#include <fstream>
#include <unordered_map>
#include <cassert>
#include <set>
class Mesh {
    using idx_t = unsigned int;
public:

    std::vector<Node> Nodes;
    std::vector<Triangle> Triangles;
    std::vector<Cell> Cells;
    explicit Mesh(const std::string& MESH_PATH);
};


#endif //FLOWMESHBUILDER_MESH_H
