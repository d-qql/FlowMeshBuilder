//
// Created by node on 12.05.2021.
//

#include <array>
#include <cmath>
#include "Interpolator.h"

double GetDistanceSquared(const Node node1, const Node node2) {
    return ((node2.x - node1.x) * (node2.x - node1.x)) + ((node2.y - node1.y) * (node2.y - node1.y)) + ((node2.z - node1.z) * (node2.z - node1.z));
}

std::array<double, 3> Interpolator(const Node& node, idx_t cellIndex, const Mesh &mesh) {
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
