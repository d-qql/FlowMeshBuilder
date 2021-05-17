//
// Created by d-qql on 28.04.2021.
//

#include "Mesh.h"

Mesh::Mesh(const std::string& MESH_PATH) {
    std::ifstream UNVmesh(MESH_PATH);
    std::unordered_multimap<idx_t, idx_t> Node2Tri;
    std::unordered_multimap<idx_t, idx_t> Tri2Cells;
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
        std::array<idx_t, 3> triNodes;
        std::set<Triangle> triSet;
        while (true) {
            UNVmesh >> id;
            if (id == -1) break;
            UNVmesh >> type;
            if (type == 11) {
                getline(UNVmesh, line);
                getline(UNVmesh, line);
                continue;
            }
//            if (type == 41) {
//                getline(UNVmesh, line);
//                UNVmesh >> node1 >> node2 >> node3;
//                if (id > Triangles.size()) Triangles.resize(id);
//                Triangles[id - 1] = Triangle(static_cast<unsigned int>(id - 1), node1, node2, node3);
//                Node2Tri.insert({node1, static_cast<unsigned int>(id)});
//                Node2Tri.insert({node2, static_cast<unsigned int>(id)});
//                Node2Tri.insert({node3, static_cast<unsigned int>(id)});
//            }
            if (type == 111) {
                getline(UNVmesh, line);
                UNVmesh >> node1 >> node2 >> node3 >> node4;
                triNodes[0] = node1;
                triNodes[1] = node2;
                triNodes[2] = node3;
                std::sort(triNodes.begin(), triNodes.end());
                triSet.insert(Triangle(0, triNodes[0], triNodes[1], triNodes[2]));
                triNodes[0] = node1;
                triNodes[1] = node2;
                triNodes[2] = node4;
                std::sort(triNodes.begin(), triNodes.end());
                triSet.insert(Triangle(0, triNodes[0], triNodes[1], triNodes[2]));
                triNodes[0] = node1;
                triNodes[1] = node3;
                triNodes[2] = node4;
                std::sort(triNodes.begin(), triNodes.end());
                triSet.insert(Triangle(0, triNodes[0], triNodes[1], triNodes[2]));
                triNodes[0] = node2;
                triNodes[1] = node3;
                triNodes[2] = node4;
                std::sort(triNodes.begin(), triNodes.end());
                triSet.insert(Triangle(0, triNodes[0], triNodes[1], triNodes[2]));
            }
        }
        Triangles.resize(triSet.size());
        unsigned int counter = 0;
        for(auto it : triSet){
            Triangles[counter] = it;
            Triangles[counter].id = counter;
            std::array<double, 3> v0 = {Nodes[Triangles[counter].nodes[1]].x - Nodes[Triangles[counter].nodes[0]].x,
                                        Nodes[Triangles[counter].nodes[1]].y - Nodes[Triangles[counter].nodes[0]].y,
                                        Nodes[Triangles[counter].nodes[1]].z - Nodes[Triangles[counter].nodes[0]].z};
            std::array<double, 3> v1 = {Nodes[Triangles[counter].nodes[2]].x - Nodes[Triangles[counter].nodes[0]].x,
                                        Nodes[Triangles[counter].nodes[2]].y - Nodes[Triangles[counter].nodes[0]].y,
                                        Nodes[Triangles[counter].nodes[2]].z - Nodes[Triangles[counter].nodes[0]].z};
            Triangles[counter].normal = VectorProduct(v0, v1) * (1./6);
            Node2Tri.insert({it.nodes[0], counter});
            Node2Tri.insert({it.nodes[1], counter});
            Node2Tri.insert({it.nodes[2], counter});
            ++counter;
        }
        UNVmesh.close();
    }else{
        std::cout<<"Can't open file!"<<std::endl;
    }
    double center_x, center_y, center_z;
    UNVmesh.open(MESH_PATH);
    if (UNVmesh.is_open()){
        std::string line;

        while (getline(UNVmesh, line)){
            //std::cout << line << std::endl;
            if(line == "  2412") break;
        }
        idx_t type, node1, node2, node3, node4;
        idx_t tri1, tri2, tri3, tri4;
        long long int id = 0;
        unsigned int cellsId = 0;
        while (true) {
            UNVmesh >> id;
            if (id == -1) break;
            UNVmesh >> type;
            if(type == 111){
                getline(UNVmesh, line);
                UNVmesh >> node1 >> node2 >> node3 >> node4;
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
                //std::cout << id << " " << tri1 << " " << tri2 << " " << tri3 << " "<< tri4 << std::endl;
                Tri2Cells.insert({tri1, cellsId});
                Tri2Cells.insert({tri2, cellsId});
                Tri2Cells.insert({tri3, cellsId});
                Tri2Cells.insert({tri4, cellsId});
                std::array<double, 3> v0 = {Nodes[node2].x - Nodes[node1].x, Nodes[node2].y - Nodes[node1].y, Nodes[node2].z - Nodes[node1].z};
                std::array<double, 3> v1 = {Nodes[node3].x - Nodes[node1].x, Nodes[node3].y - Nodes[node1].y, Nodes[node3].z - Nodes[node1].z};
                std::array<double, 3> v2 = {Nodes[node4].x - Nodes[node1].x, Nodes[node4].y - Nodes[node1].y, Nodes[node4].z - Nodes[node1].z};
                center_x = (Nodes[node1].x + Nodes[node2].x + Nodes[node3].x + Nodes[node4].x) / 4;
                center_y = (Nodes[node1].y + Nodes[node2].y + Nodes[node3].y + Nodes[node4].y) / 4;
                center_z = (Nodes[node1].z + Nodes[node2].z + Nodes[node3].z + Nodes[node4].z) / 4;
                Cells.emplace_back(cellsId, tri1, tri2, tri3, tri4, Node{center_x, center_y, center_z}, TripleProduct3(v0, v1, v2) / 6.);
                ++cellsId;
            }
        }
        for( auto cell: Cells){
            for(idx_t tri = 0; tri < 4; ++tri){
                std::pair<UMMAPIterator, UMMAPIterator> tri2cellIT = Tri2Cells.equal_range(cell.triangles[tri]);
                for(UMMAPIterator it = tri2cellIT.first; it != tri2cellIT.second; ++it){
                    //std::cout<<it->second<<std::endl;
                    if( it->second != cell.id ) cell.neighbours.insert({cell.triangles[tri], it->second});
                }
                //std::cout<<std::endl;
            }
            std::cout<<cell.neighbours.size()<<std::endl;
            assert(cell.neighbours.size() <= 4 && "TOO MUCH NEIGHBOURS! BADABUM! DIMA IS DIED");
            assert(!cell.neighbours.empty() && "TOO LOW NEIGHBOURS! BADABUM! DIMA HAS DIED");
        }
        UNVmesh.close();
    }else{
        std::cout<<"Can't open file!"<<std::endl;
    }
    for(auto n : Triangles){
        std::cout<<n.id<<n<<std::endl;
    }

}