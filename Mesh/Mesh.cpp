//
// Created by d-qql on 28.04.2021.
//

#include "Mesh.h"
#include <cassert>
Mesh::Mesh(std::ifstream& UNVmesh) {
    std::unordered_multimap<idx_t, idx_t> Node2Tri;
    typedef std::unordered_multimap<idx_t, idx_t>::iterator UMMAPIterator;
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
            UNVmesh >> x >> y >> z;
            if (id > Nodes.size()) Nodes.resize(id);
            Nodes[id - 1] = Node({x, y, z});
        }

        while (getline(UNVmesh, line)) // ищем начало элементов
        {
            //std::cout << line << std::endl;
            if(line == "  2412") break;
        }
        idx_t type, node1, node2, node3, node4;
        idx_t tri1, tri2, tri3, tri4;
        while (true) {
            UNVmesh >> id;
            if (id == -1) break;
            UNVmesh >> type;
            if (type == 11) {
                getline(UNVmesh, line);
                getline(UNVmesh, line);
                continue;
            }
            if (type == 41) {
                getline(UNVmesh, line);
                UNVmesh >> node1 >> node2 >> node3;
                if (id > Triangles.size()) Triangles.resize(id);
                Triangles[id - 1] = Triangle(static_cast<unsigned int>(id - 1), node1, node2, node3);
                Node2Tri.insert({node1, static_cast<unsigned int>(id)});
                Node2Tri.insert({node2, static_cast<unsigned int>(id)});
                Node2Tri.insert({node3, static_cast<unsigned int>(id)});
            }
            if (type == 111) {
                getline(UNVmesh, line);
                UNVmesh >> node1 >> node2 >> node3 >> node4;
                if (id > Cells.size()) Cells.resize(id);
                std::pair<UMMAPIterator, UMMAPIterator> nd1 = Node2Tri.equal_range(node1);
                std::pair<UMMAPIterator, UMMAPIterator> nd2 = Node2Tri.equal_range(node2);
                std::pair<UMMAPIterator, UMMAPIterator> nd3 = Node2Tri.equal_range(node3);
                std::pair<UMMAPIterator, UMMAPIterator> nd4 = Node2Tri.equal_range(node4);
                std::vector<idx_t> ndv1, ndv2, ndv3, ndv4;
                std::transform(nd1.first, nd1.second,std::back_inserter(ndv1), [](std::pair<idx_t, idx_t> element){return element.second;});
                std::transform(nd2.first, nd2.second,std::back_inserter(ndv2), [](std::pair<idx_t, idx_t> element){return element.second;});
                std::transform(nd3.first, nd3.second,std::back_inserter(ndv3), [](std::pair<idx_t, idx_t> element){return element.second;});
                std::transform(nd4.first, nd4.second,std::back_inserter(ndv4), [](std::pair<idx_t, idx_t> element){return element.second;});
                std::sort(ndv1.begin(), ndv1.end());
                std::sort(ndv2.begin(), ndv2.end());
                std::sort(ndv3.begin(), ndv3.end());
                std::sort(ndv4.begin(), ndv4.end());
                std::vector<idx_t> v_intersection12, v_intersection13, v_intersection14,
                v_intersection23, v_intersection24, v_intersection34,
                v_intersection123, v_intersection124, v_intersection234, v_intersection134;
                std::set_intersection(ndv1.begin(), ndv1.end(),
                                      ndv2.begin(), ndv2.end(),
                                      std::back_inserter(v_intersection12));
                std::set_intersection(ndv1.begin(), ndv1.end(),
                                      ndv3.begin(), ndv3.end(),
                                      std::back_inserter(v_intersection13));
                std::set_intersection(ndv1.begin(), ndv1.end(),
                                      ndv4.begin(), ndv4.end(),
                                      std::back_inserter(v_intersection14));
                std::set_intersection(ndv2.begin(), ndv2.end(),
                                      ndv3.begin(), ndv3.end(),
                                      std::back_inserter(v_intersection23));
                std::set_intersection(ndv2.begin(), ndv2.end(),
                                      ndv4.begin(), ndv4.end(),
                                      std::back_inserter(v_intersection24));
                std::set_intersection(ndv3.begin(), ndv3.end(),
                                      ndv4.begin(), ndv4.end(),
                                      std::back_inserter(v_intersection34));
                std::set_intersection(v_intersection12.begin(), v_intersection12.end(),
                                      v_intersection23.begin(), v_intersection23.end(),
                                      std::back_inserter(v_intersection123));
                std::set_intersection(v_intersection12.begin(), v_intersection12.end(),
                                      v_intersection24.begin(), v_intersection24.end(),
                                      std::back_inserter(v_intersection124));
                std::set_intersection(v_intersection13.begin(), v_intersection13.end(),
                                      v_intersection34.begin(), v_intersection34.end(),
                                      std::back_inserter(v_intersection134));
                std::set_intersection(v_intersection23.begin(), v_intersection23.end(),
                                      v_intersection34.begin(), v_intersection34.end(),
                                      std::back_inserter(v_intersection234));

#ifndef NDEBUG
                assert(v_intersection123.size() == 1 && "wrong triangle 123");
                assert(v_intersection124.size() == 1 && "wrong triangle 124");
                assert(v_intersection134.size() == 1 && "wrong triangle 134");
                assert(v_intersection234.size() == 1 && "wrong triangle 234");
#endif
                tri1 = v_intersection123[0];
                tri2 = v_intersection124[0];
                tri3 = v_intersection134[0];
                tri4 = v_intersection234[0];
                std::cout << id << " " << tri1 << " " << tri2 << " " << tri3 << " "<< tri4 << std::endl;
            }
        }
    }else{
        std::cout<<"Can't open file!"<<std::endl;
    }
    for(auto n : Triangles){
        std::cout<<n<<std::endl;
    }

}