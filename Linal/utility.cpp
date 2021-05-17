//
// Created by d-qql on 17.05.2021.
//

#include "utility.h"

double TripleProduct3(const std::array<double, 3>& v0, const std::array<double, 3>& v1, const std::array<double, 3>& v2){
    return v0[0] * v1[1] * v2[2] + v1[0] * v2[1] * v0[2] + v2[0] * v0[1] + v1[2]
            - v0[2] * v1[1] * v2[0] - v0[0] * v2[1] * v1[2] - v1[0] * v0[1] * v2[2];
}

std::array<double, 3> VectorProduct(const std::array<double, 3>& v0, const std::array<double, 3>& v1){
    return std::array<double, 3>{v0[1] * v1[2] - v0[2] * v1[1], -(v0[0] * v1[2] - v0[2] * v1[0]), v0[0] * v1[1] - v1[0] * v0[1]};
}

std::array<double, 3> operator*=(std::array<double, 3> arr, double k){
    for(auto& elm : arr){
        elm *= k;
    }
    return arr;
}

std::array<double, 3> operator*(std::array<double, 3> arr, double k){
    for(auto& elm : arr){
        elm *= k;
    }
    return arr;
}