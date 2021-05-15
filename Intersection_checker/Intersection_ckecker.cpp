#include "Intersection_ckecker.h"

// проверяет пересечение с треугольником. Возвращает расстояние t, если пересечение есть, -1 иначе
double checkTriangle(const Node &O, double vx, double vy, double vz, idx_t triangleIndex, const Mesh &mesh) {
    node A = mesh.Nodes[mesh.Triangles[triangleIndex].nodes[0]];
    node B = mesh.Nodes[mesh.Triangles[triangleIndex].nodes[1]];
    node C = mesh.Nodes[mesh.Triangles[triangleIndex].nodes[2]];

    node T, E1, E2;
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
    // Если детерминант близок к нулю - решения нет
    /*
     if (-epsilon < det && det < epsilon)
        return -1;
     */

    double det2 = -vx * (T.y * E2.z - T.z * E2.y) - T.x * (-vy * E2.z + vz * E2.y) + E2.x * (-vy * T.z + vz * T.y);
    double u = det2 / det;
    if (u < 0 || u > 1)
        return -1;

    double det3 = -vx * (E1.y * T.z - E1.z * T.y) - E1.x * (-vy * T.z + vz * T.y) + T.x * (-vy * E1.z + vz * E1.y);
    double w = det3/det;
    if (w < 0 || w > 1 || u + w > 1)
        return -1;

    double det1 =
            T.x * (E1.y * E2.z - E1.z * E2.y) - E1.x * (T.y * E2.z - T.z * E2.y) + E2.x * (T.y * E1.z - T.z * E1.y);
    double t = det1/det;
    if (t < 0)
        return -1;
    return t;
}

idx_t findIntersection(const Node& node1, const Node& node2, idx_t cellIndex, const Mesh& mesh) {
    vx = node2.x - node1.x;
    vy = node2.y - node1.y;
    vz = node2.z - node1.z;

    for (int i = 0; i < 4; ++i) {
        t = checkTriangle(node1, vx, vy, vz, mesh.Cells[cellIndex].triangles[i], mesh);
        if (t != -1) {
            if (t > 1)
                return -1;
            else
                return mesh.Cells[cellIndex].triangles[i];
        }
    }
    return -1;
}