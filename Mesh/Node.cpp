//
// Created by d-qql on 29.04.2021.
//
#include "Node.h"

std::ostream& operator<<(std::ostream& os, Node& n){
    os << "( " << n.x << ", " << n.y << ", " << n.z << " )\n";
    return os;
}