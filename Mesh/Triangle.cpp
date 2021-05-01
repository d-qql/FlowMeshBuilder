//
// Created by d-qql on 28.04.2021.
//

#include "Triangle.h"


Triangle::Triangle(idx_t id, idx_t node1, idx_t node2, idx_t node3){
    this->id = id;
/*#ifndef NDEBUG
    nodes.at(0) = node1;
    nodes.at(1) = node2;
    nodes.at(2) = node3;
#else
    nodes[0] = node1;
    nodes[1] = node2;
    nodes[2] = node3;
#endif*/
    nodes.at(0) = node1;
    nodes.at(1) = node2;
    nodes.at(2) = node3;

}
std::ostream& operator<<(std::ostream& os, const Triangle& Tri){
    os << "( " << Tri.nodes[0] << " " << Tri.nodes[1] << " " << Tri.nodes[2]<<" )\n";
    return os;
}