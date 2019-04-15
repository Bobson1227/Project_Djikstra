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
            return v1.distance < v2.distance;
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



    void Graph::vertexes_exist( std::string name1, std::string name2)
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



    bool Graph::node_exist( std::string name)
    {
        for (int i = 0; i < static_cast<int>(m_vertex.size()); i++)
        {
            if (name == m_vertex[i].name)
                return true;
        }
        return false;
    }



    void Graph::add_node( std::string name)
    {
        m_vertex.resize(m_vertex.size() + 1 );
        m_vertex[m_vertex.size()-1].name = name;
        m_map[name] = m_vertex.size()-1;
    }



    void Graph::add_edge( std::string name1, std::string name2, float dist )
    {
        int id1 = m_map[ name1 ], id2 = m_map[ name2 ];
        int edges_size1, edges_size2;

        edges_size1 = m_vertex[id1].edges.size();
        edges_size2 = m_vertex[id2].edges.size();
        m_vertex[id1].edges.resize(edges_size1 + 1);
        m_vertex[id2].edges.resize(edges_size2 + 1);

        m_vertex[id1].edges[edges_size1].source_id = id1;
        m_vertex[id1].edges[edges_size1].target_id = id2;
        m_vertex[id1].edges[edges_size1].distance = dist;

        m_vertex[id2].edges[edges_size2].source_id = id2;
        m_vertex[id2].edges[edges_size2].target_id = id1;
        m_vertex[id2].edges[edges_size2].distance = dist;
    }


     
    Vertex Graph::get_node( int id )
    {
        return m_vertex[id];
    }
	


    float Graph::target_distance(int id)
    {
        int parent_id = 0 , edge_id = 0;
        float distance = 0;

        while(true){
            parent_id = m_vertex[id].parent_id;

            if (parent_id < 0)
                break;

            for (int i = 0; i < static_cast<int>(m_vertex[parent_id].edges.size()); ++i)
            {
                if (id == m_vertex[parent_id].edges[i].target_id)
                {
                    edge_id = i;
                    break;
                }
            }

            distance += m_vertex[parent_id].edges[edge_id].distance;

            id = parent_id;
        }

        return distance;
    }
	


     bool Graph::is_longer(int id1, int id2, float dist)
     {
         return (target_distance(id1) + dist > target_distance(id2));
     }



     void Graph::shortest_way(std::string name1, std::string name2)
     {
         m_vertex[m_map[name1]].distance = 0;

         Vertex node;

         std::priority_queue <Vertex, std::deque<Vertex>, Comparator> queue;

         queue.push(m_vertex[m_map[name1]]);

         while (queue.top().distance < m_vertex[m_map[name2]].distance)
         {
             node = get_node(m_map[queue.top().name]);

             if (node.visited != 1)
             {
                 for (int i = 0; i < static_cast<int>(node.edges.size()); i++)
                 {
                     if (!is_longer(m_map[node.name], node.edges[i].target_id, node.edges[i].distance))
                     {
                         m_vertex[node.edges[i].target_id].distance = target_distance(m_map[node.name]) + node.edges[i].distance;
                         queue.push(m_vertex[node.edges[i].target_id]);
                         m_vertex[node.edges[i].target_id].visited = 0;
                         m_vertex[node.edges[i].target_id].parent_id = m_map[node.name];
                     }
                 }
                 m_vertex[m_map[node.name]].visited = 1;
             }

             queue.pop();
         }
     }


     
    void Graph::write_data(std::string name)
    {
        int id = m_map[ name ] ;

        std::fstream file;
        file.open("destination.txt" , std::ios::out);

        while (true)
        {
            if (id <= 0)
                break;

            file << m_vertex[id].name << " " << m_vertex[id].distance << std::endl;
            id = m_vertex[id].parent_id;
        }

        file.close();
    }
}