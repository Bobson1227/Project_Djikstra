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
        bool operator()(const Vertex& v1, const Vertex& v2)
        {
            return v1.distance > v2.distance;
        }
    };



    void Graph::load_graph(const std::string& file_name) 
    {
        std::string name1, name2;
        float dist = 0;

        std::fstream file_data;
        file_data.open(file_name, std::ios::in);

        try 
        {
            if (!file_data.good())
            {
                throw std::invalid_argument("File can not be loaded");
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
        }
        catch (const std::invalid_argument& e)
        {
            std::cout << "Invalid argument: " << e.what() << std::endl;
        }

        file_data.close();
    }



    void Graph::vertexes_exist(const std::string& name1, const std::string& name2)
    {
        try
        {
            if (!node_exist(name1))
            {
                throw std::invalid_argument("First vertex not exist");
            }
            if (!node_exist(name2))
            {
                throw std::invalid_argument("Second vertex not exist");
            }
        }
        catch (const std::invalid_argument& e)
        {
            std::cout << "Invalid argument: " << e.what() << std::endl;
        }
    }



    bool Graph::node_exist(const std::string& name)
    {
        if(m_map.count(name)!=0)
            return true;
        return false;
    }



    void Graph::add_node(const std::string& node_name)
    {
        m_vertex.emplace_back(Vertex(node_name));
        m_map[node_name] = m_vertex.size()-1;
    }



    void Graph::add_edge(const std::string& name1, const std::string& name2, float dist )
    {
        int id1 = m_map[ name1 ], id2 = m_map[ name2 ];
        
        m_vertex[id1].edges.emplace_back(Edge{ id1, id2, dist });
        m_vertex[id2].edges.emplace_back(Edge{ id2, id1, dist });
    }
    
    

    bool Graph::is_shorter(int id1, int id2, float dist)
    {
        return (m_vertex[id1].distance + dist < m_vertex[id2].distance);
    }

    
    void Graph::shortest_way(const std::string& name1, const std::string& name2)
    {
        vertexes_exist(name1, name2);
            

        m_vertex[m_map[name1]].distance = 0;
        std::priority_queue <Vertex, std::deque<Vertex>, Comparator> queue;
        queue.push(m_vertex[m_map[name1]]);

        // while the closest is closer than the destination
        while ((queue.empty()) && (queue.top().distance < m_vertex[m_map[name2]].distance))
        {
           const Vertex& node = m_vertex[m_map[queue.top().name]];

            if (node.visited != 1)
            {
                for (size_t i = 0; i < node.edges.size(); i++)
                {
                    if (is_shorter(m_map[node.name], node.edges[i].target_id, node.edges[i].distance))
                    {
                        m_vertex[node.edges[i].target_id].distance = m_vertex[m_map[node.name]].distance + node.edges[i].distance;
                        queue.push( m_vertex[node.edges[i].target_id]);
                        m_vertex[node.edges[i].target_id].visited = false;
                        m_vertex[node.edges[i].target_id].parent_id = m_map[node.name];
                    }
                }
                m_vertex[m_map[node.name]].visited = true;
            }

                queue.pop();
        }
    }


     
    void Graph::write_data(const std::string& name, const std::string& file_name)
    {
        int id = m_map[ name ] ;

        std::fstream file;
        file.open(file_name , std::ios::out);

        while (true)
        {
            file << m_vertex[id].name << " " << m_vertex[id].distance << std::endl;

            if (m_vertex[id].parent_id==-1)
                break;

            id = m_vertex[id].parent_id;
        }

        file.close();
    }
}
