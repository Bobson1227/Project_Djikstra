#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <map>


namespace Graph
{
    struct Edge
    {
        int source_id;
        int target_id;
        float distance = std::numeric_limits<float>::infinity();
    };

    struct Vertex
    {
        std::string name;
        std::vector <Edge> edges;
        int parent_id = -1;
        bool visited = 0;
        float distance = std::numeric_limits<float>::infinity();
    };

    class Graph
    {
    public:
        std::vector <Vertex> m_vertex;
        std::map< std::string, int> m_map;


        void load_graph();
        void vertexes_exist(const std::string& name1, const std::string& name2);
        bool node_exist(const std::string& name );
        void add_node(std::string name );
        void add_edge(const std::string& name1, const std::string&  name2, float dist );
        Vertex get_node( int id );
        bool is_shorter(int id1, int id2, float dist );
        void shortest_way(const std::string& name1, const std::string&);
        void write_data(const std::string& name);
    };
}