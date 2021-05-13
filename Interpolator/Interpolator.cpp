//
// Created by node on 12.05.2021.
//

#include <array>
#include <complex>
#include "Interpolator.h"

double GetDistanceSquared(const Node node1, const Node node2) {
    return std::pow((node2.x - node1.x), 2) + std::pow((node2.y - node1.y), 2) + std::pow((node2.z - node1.z), 2);
}

std::array<double, 3> Interpolator(const Node node, idx_t cellIndex, const Mesh &mesh) {
    std::array<double, 3> InterpolatedField = {0., 0., 0.};
    std::vector<idx_t> Neighbours;
    Neighbours.push_back(cellIndex);
    Neighbours.insert(Neighbours.begin(), mesh.InternalCells.at(cellIndex).neighbours.begin(), mesh.InternalCells.at(cellIndex).neighbours.end());

    double DistanceSum = 0;
    unsigned int N = Neighbours.size();
    std::vector<double> Distances;
    Distances.resize(N);
    for (std::vector<idx_t>::iterator it = Neighbours.begin(); it != Neighbours.end(); ++it) {
        double CurrentDistance = sqrt(GetDistanceSquared(node, mesh.InternalCells.at(*it).center_pos));
        Distances.push_back(CurrentDistance);
        DistanceSum += CurrentDistance;
    }
    for (unsigned int j = 0; j < Neighbours.size(); ++j) {
        double CurrentWeight = (2/N - Distances[j] / DistanceSum);
        for (unsigned int i = 0; i < 3; ++i)
            InterpolatedField[i] += mesh.InternalCells.at(Neighbours[j]).vector_val[i] * CurrentWeight;
    }
    return InterpolatedField;
}
