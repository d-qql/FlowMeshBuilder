//
// Created by d-qql on 28.04.2021.
//

#ifndef FLOWMESHBUILDER_NODE_H
#define FLOWMESHBUILDER_NODE_H

#include <iostream>
struct Node {
    using idx_t = unsigned int;
    idx_t id;
    double x;
    double y;
    double z;
};

std::ostream& operator<<(std::ostream& os, Node& n);

#endif //FLOWMESHBUILDER_NODE_H
