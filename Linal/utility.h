//
// Created by d-qql on 17.05.2021.
//

#ifndef FLOWMESHBUILDER_UTILITY_H
#define FLOWMESHBUILDER_UTILITY_H
#include <array>

double TripleProduct3(const std::array<double, 3>& v0, const std::array<double, 3>& v1, const std::array<double, 3>& v2);

std::array<double, 3> CrossProduct(const std::array<double, 3>& v0, const std::array<double, 3>& v1);

std::array<double, 3> operator*=(std::array<double, 3> arr, double k);
std::array<double, 3> operator*(std::array<double, 3> arr, double k);

#endif //FLOWMESHBUILDER_UTILITY_H
