//
// Created by d-qql on 28.04.2021.
//

#include "Mesh.h"

Mesh::Mesh(std::ifstream& UNVmesh) {
    std::unordered_multimap<idx_t, idx_t> Node2Tri;
    std::cout << "hui" << UNVmesh.is_open() << std::endl;
    if (UNVmesh.is_open())
    {
        std::string line;
        while (getline(UNVmesh, line)) // ищем начало нодов
        {
            std::cout << line << std::endl;
            if(line == "  2411") break;
        }
        long long int id = 0;
        double x, y, z;
        int temp;
        while(true){
            UNVmesh >> id;
            if( id == -1) break;
            UNVmesh >> temp;
            UNVmesh >> temp;
            UNVmesh >> temp;
            //std::cout << "pizds" << std::endl;
            UNVmesh >> x >> y >> z;
            Nodes.insert({static_cast<unsigned int>(id), Node({x, y, z})});
        }

        while (getline(UNVmesh, line)) // ищем начало элементов
        {
            //std::cout << line << std::endl;
            if(line == "  2412") break;
        }
        idx_t type, node1, node2, node3;
        while (true){
            UNVmesh >> id >> type;
            if( type == 11){
                getline(UNVmesh, line);
                getline(UNVmesh, line);
                continue;
            }
            if( type == 41){
                getline(UNVmesh, line);
                UNVmesh >> node1 >> node2 >> node3;
                Triangles.insert({static_cast<unsigned int>(id), Triangle(static_cast<unsigned int>(id), node1, node2, node3)});
            }

            if( type == -1 ) break;
        }
    }else{
        std::cout<<"Can't open file!"<<std::endl;
    }
    for(auto n : Triangles){
        std::cout<<n.first<<n.second<<std::endl;
    }

}