#include <vector>
#include <queue>
#include <deque>
#include <map>
#include <fstream>
#include <string>


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



    void Graph::load_graph() {
        std::string name1, name2;
        float dist = 0;

        std::fstream file_data;
        file_data.open("distances.txt", std::ios::in);

        if (file_data.good() == false)
        {
            std::cout << "Error with oppening";
            exit(1);
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



    void Graph::vertexes_exist(const std::string& name1, const std::string& name2)
    {
        bool end1 = 0, end2 = 0;

        if (!node_exist(name1))
        {
            std::cout << name1 << " not exist." << std::endl;
            end1 = 1;
        }
        if (!node_exist(name2))
        {
            std::cout << name2 << " not exist." << std::endl;
            end2 = 1;
        }
        if (end1 || end2)
        {
            system("pause");
            exit(1);
        }
    }



    bool Graph::node_exist(const std::string& name)
    {
        for (size_t i = 0; i < m_vertex.size(); i++)
        {
            if (name == m_vertex[i].name)
                return true;
        }
        return false;
    }



    void Graph::add_node( std::string name)
    {
        m_vertex.emplace_back(Vertex{ name = name });
        m_map[name] = m_vertex.size()-1;
    }



    void Graph::add_edge(const std::string& name1, const std::string& name2, float dist )
    {
        int id1 = m_map[ name1 ], id2 = m_map[ name2 ];
        
        m_vertex[id1].edges.emplace_back(Edge{ id1, id2, dist });
        m_vertex[id2].edges.emplace_back(Edge{ id2, id1, dist });
    }


     
    Vertex Graph::get_node( int id )
    {
        return m_vertex[id];
    }
    
    

    bool Graph::is_shorter(int id1, int id2, float dist)
    {
        return (m_vertex[id1].distance + dist < m_vertex[id2].distance);
    }



     void Graph::shortest_way(const std::string& name1, const std::string& name2)
     {
         m_vertex[m_map[name1]].distance = 0;
         Vertex node;
         std::priority_queue <Vertex, std::deque<Vertex>, Comparator> queue;
         queue.push(m_vertex[m_map[name1]]);

         // while the closest is closer than the destination
         while (queue.top().distance < m_vertex[m_map[name2]].distance)
         {
             if (queue.empty())
             {
                 std::cout << "There is an error, cities are not connected" << std::endl;
                 exit(1);
             }
             node = get_node(m_map[queue.top().name]);

             if (node.visited != 1)
             {
                 for (size_t i = 0; i < node.edges.size(); i++)
                 {
                     if (is_shorter(m_map[node.name], node.edges[i].target_id, node.edges[i].distance))
                     {
                         m_vertex[node.edges[i].target_id].distance = m_vertex[m_map[node.name]].distance + node.edges[i].distance;
                         queue.push( m_vertex[node.edges[i].target_id]);
                         m_vertex[node.edges[i].target_id].visited = 0;
                         m_vertex[node.edges[i].target_id].parent_id = m_map[node.name];
                     }
                 }
                 m_vertex[m_map[node.name]].visited = 1;
             }

                 queue.pop();
         }
     }


     
    void Graph::write_data(const std::string& name)
    {
        int id = m_map[ name ] ;

        std::fstream file;
        file.open("destination.txt" , std::ios::out);

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