//
// Created by d-qql on 28.04.2021.
//

#ifndef FLOWMESHBUILDER_CELL_H
#define FLOWMESHBUILDER_CELL_H

#include <vector>
#include "Triangle.h"
class Cell {

using idx_t = unsigned int;

public:

    idx_t id;
    std::array<idx_t, 4> triangles; //треугольники, составляющие ячейку
    std::vector<idx_t> neighbours;  //индексы соседних ячеек
    Node center_pos;    //центральная точка
    double scalar_val;
    std::array<double, 3> vector_val;
};




#endif //FLOWMESHBUILDER_CELL_H
