#include <vector>
#include <queue>
#include <deque>
#include <map>
#include <fstream>
#include <string>
#include <stdexcept>


#include "Graph.h"


namespace Graph
{
    class Comparator {
    public:
        bool operator()(const Vertex* v1, const Vertex* v2)
        {
            return v1->distance > v2->distance;
        }
    };



    void Graph::assert_vertexes_exist(const std::string& vertex_name1, const std::string& vertex_name2)
    {
        if (!node_exist(vertex_name1))
        {
            throw std::invalid_argument("First vertex not exist");
        }
        if (!node_exist(vertex_name2))
        {
            throw std::invalid_argument("Second vertex not exist");
        }
    }



    bool Graph::node_exist(const std::string& vertex_name)
    {
        return (m_map.count(vertex_name) != 0);
    }



    void Graph::add_node(const std::string& vertex_name)
    {
        m_vertex.emplace_back(Vertex(vertex_name));
        m_map[vertex_name] = m_vertex.size()-1;
    }



    void Graph::add_edge(const std::string& vertex_name1, const std::string& name2, float dist )
    {
        int id1 = m_map[vertex_name1 ], id2 = m_map[ name2 ];
        
        m_vertex[id1].edges.emplace_back(Edge{ id1, id2, dist });
        m_vertex[id2].edges.emplace_back(Edge{ id2, id1, dist });
    }



    void Graph::load_graph(const std::string& file_name)
    {
        std::string name1, name2;
        float dist = 0;

        std::fstream file_data;
        file_data.open(file_name, std::ios::in);

        if (!file_data.good())
        {
            throw std::ios_base::failure(file_name);
        }

        while (!file_data.eof())
        {
            file_data >> name1 >> name2 >> dist;

            if (!node_exist(name1))
            {
                add_node(name1);
            }
            if (!node_exist(name2))
            {
                add_node(name2);
            }
            add_edge(name1, name2, dist);
        }

        file_data.close();
    }
    
    

    bool Graph::is_shorter(int id1, int id2, float dist)
    {
        return (m_vertex[id1].distance + dist < m_vertex[id2].distance);
    }

    
    void Graph::shortest_way(const std::string& vertex_name1, const std::string& vertex_name2)
    {
        assert_vertexes_exist(vertex_name1, vertex_name2);
            

        m_vertex[m_map[vertex_name1]].distance = 0;
        std::priority_queue <const Vertex*, std::deque<const Vertex*>, Comparator> queue;
        queue.push(&m_vertex[m_map[vertex_name1]]);

        // while the closest is closer than the destination
        while ((!queue.empty()) && (queue.top()->distance < m_vertex[m_map[vertex_name2]].distance))
        {
            const Vertex& node = *queue.top();
            const size_t node_id = m_map[node.name];

            if (node.visited != 1)
            {
                for (const auto& edge : node.edges)
                {
                    if (is_shorter(node_id, edge.target_id, edge.distance))
                    {
                        m_vertex[edge.target_id].distance = m_vertex[node_id].distance + edge.distance;
                        queue.push(&m_vertex[edge.target_id]);
                        m_vertex[edge.target_id].visited = false;
                        m_vertex[edge.target_id].parent_id = node_id;
                    }
                }
                m_vertex[node_id].visited = true;
            }

                queue.pop();
        }
    }


     
    void Graph::write_data(const std::string& vertex_name, const std::string& file_name)
    {
        int id = m_map[ vertex_name ] ;

        std::fstream file;
        file.open(file_name , std::ios::out);

        while (id != -1)
        {
            file << m_vertex[id].name << " " << m_vertex[id].distance << std::endl;
            id = m_vertex[id].parent_id;
        }


        file.close();
    }
}
