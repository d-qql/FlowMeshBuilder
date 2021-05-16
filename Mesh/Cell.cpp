//
// Created by d-qql on 28.04.2021.
//

#include "Cell.h"

Cell::Cell(idx_t id, idx_t tri1, idx_t tri2, idx_t tri3, idx_t tri4, const Node& center){
    this->id = id;
    triangles[0] = tri1;
    triangles[1] = tri2;
    triangles[2] = tri3;
    triangles[3] = tri4;
    this->center_pos = center;
}