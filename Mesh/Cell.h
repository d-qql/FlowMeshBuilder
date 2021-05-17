//
// Created by d-qql on 28.04.2021.
//

#ifndef FLOWMESHBUILDER_CELL_H
#define FLOWMESHBUILDER_CELL_H

#include <vector>
#include "Triangle.h"
#include <unordered_map>
class Cell {

using idx_t = unsigned int;

public:

    idx_t id;
    std::array<idx_t, 4> triangles; //треугольники, составляющие ячейку
    std::unordered_map<idx_t, idx_t> neighbours;  //индексы соседних ячеек по треугольнику
    Node center_pos;    //центральная точка
    double scalar_val;
    std::array<double, 3> vector_val;
    Cell(idx_t id, idx_t tri1, idx_t tri2, idx_t tri3, idx_t tri4, const Node& center);
};




#endif //FLOWMESHBUILDER_CELL_H
