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
        float distance = std::numeric_limits<float>::signaling_NaN();
    };

    struct Vertex
    {
        std::string name;
        std::vector <Edge> edges;
        int parent_id = -1;
        bool visited = false;
        float distance = std::numeric_limits<float>::infinity();

        Vertex(const std::string& name) : name(name) {}
        Vertex(Vertex&& other) = default;
        Vertex(const Vertex&) = delete;
        Vertex operator=(const Vertex&) = delete;
    };
    
    class Graph
    {
    private:
        std::vector <Vertex> m_vertex;
        std::map< std::string, int> m_map;

        void assert_vertexes_exist(const std::string& vertex_name1, const std::string& vertex_name2);
        bool node_exist(const std::string& vertex_name);
        void add_node(const std::string& vertex_name);
        void add_edge(const std::string& vertex_name1, const std::string&  vertex_name2, float dist);
        bool is_shorter(int id1, int id2, float dist);
        

    public:
        void load_graph(const std::string& file_name);
        void shortest_way(const std::string& vertex_name1, const std::string& vertex_name2);
        void write_data(const std::string& vertex_name, const std::string& file_name);
    };
}
