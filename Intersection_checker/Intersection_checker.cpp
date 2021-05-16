#include "Intersection_checker.h"

// проверяет пересечение с треугольником. Возвращает расстояние t, если пересечение есть, -1 иначе
double checkTriangle(const Node &O, double vx, double vy, double vz, idx_t triangleIndex, const Mesh &mesh) {
    Node A = mesh.Nodes[mesh.Triangles[triangleIndex].nodes[0]];
    Node B = mesh.Nodes[mesh.Triangles[triangleIndex].nodes[1]];
    Node C = mesh.Nodes[mesh.Triangles[triangleIndex].nodes[2]];

    Node T, E1, E2;
    T.x = O.x - A.x;
    T.y = O.y - A.y;
    T.z = O.z - A.z;

    E1.x = B.x - A.x;
    E1.y = B.y - A.y;
    E1.z = B.z - A.z;

    E2.x = C.x - A.x;
    E2.y = C.y - A.y;
    E2.z = C.z - A.z;

    double det = -vx * (E1.y * E2.z - E1.z * E2.y) - E1.x * (-vy * E2.z + vz * E2.y) + E2.x * (-vy * E1.z + vz * E1.y);
    std::cout << det << std::endl;
    // Если детерминант близок к нулю - решения нет
    double epsilon = 1e-3;
    if (-epsilon < det && det < epsilon)
        return -1;


    double det2 = -vx * (T.y * E2.z - T.z * E2.y) - T.x * (-vy * E2.z + vz * E2.y) + E2.x * (-vy * T.z + vz * T.y);
    double u = det2 / det;
    if (u < 0 || u > 1)
        return -1;

    double det3 = -vx * (E1.y * T.z - E1.z * T.y) - E1.x * (-vy * T.z + vz * T.y) + T.x * (-vy * E1.z + vz * E1.y);
    double w = det3 / det;
    if (w < 0 || w > 1 || u + w > 1)
        return -1;

    double det1 =
            T.x * (E1.y * E2.z - E1.z * E2.y) - E1.x * (T.y * E2.z - T.z * E2.y) + E2.x * (T.y * E1.z - T.z * E1.y);
    double t = det1 / det;
    if (t < 0)
        return -1;
    return t;
}

idx_t findIntersection(const Node &node1, const Node &node2, idx_t cellIndex, const Mesh &mesh) {
    double vx = node2.x - node1.x;
    double vy = node2.y - node1.y;
    double vz = node2.z - node1.z;

    for (int i = 0; i < 4; ++i) {
        double t = checkTriangle(node1, vx, vy, vz, mesh.Cells[cellIndex].triangles[i], mesh);
        if (t > 0) {
            if (t > 1)
                return cellIndex;
            else
                for (int j = 0; j < mesh.Cells[cellIndex].neighbours.size(); ++j) {
                    for (int k = 0; k < 4; ++k) {
                        if (mesh.Cells[cellIndex].triangles[i] ==
                            mesh.Cells[mesh.Cells[cellIndex].neighbours[j]].triangles[k])
                            return mesh.Cells[cellIndex].neighbours[j];
                    }
                }
        }
    }
    return cellIndex;
}