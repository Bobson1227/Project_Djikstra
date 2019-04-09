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
        const std::vector<Vertex>& m_priorities;
    public:
        Comparator(const std::vector<Vertex>& priorities) : m_priorities(priorities) {}

        bool operator()(size_t id1, size_t id2)
        {
            return m_priorities[id1].distance < m_priorities[id2].distance;
        }
    };


    void Graph::shortest_way(std::string name1, std::string name2)
    {
        size_t id1, id2;

        Comparator comparator(m_vertex);

        std::priority_queue <Vertex, std::deque<Vertex>, Comparator> queue(comparator);

        for (size_t i = 0; i < m_vertex.size(); i++)
        {
            if (m_vertex[i].name == name1)
            {
                id1 = i;
            }
            if (m_vertex[i].name == name2)
            {
                id2 = i;
            }
        }

        queue.push(m_vertex[id1]);

        while (queue.top().distance < m_vertex[id2].distance)
        {
            for (size_t i; i < queue.top().edges.size(); i++)
            {
                
                m_vertex[queue.top().edges[i].target_id].distance = target_distance(queue.top().edges[i].target_id);
                queue.push(m_vertex[queue.top().edges[i].target_id]);
            }

            queue.pop();
        }
    }




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



     bool Graph::node_exist( std::string name)
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
		m_vertex.resize(m_vertex.size() + 1 );
		m_vertex[m_vertex.size()-1].name = name;
   	}



	void Graph::add_edge( std::string name1, std::string name2, float dist )
	{
		int id1=0, id2=0;
		int edges_size1, edges_size2;

          for (size_t i = 0; i < m_vertex.size(); i++)
          {
              if (m_vertex[i].name == name1)
              {
                  id1 = i;
              }
              if (m_vertex[i].name == name2)
              {
                  id2 = i;
              }
          }
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


     
	Vertex Graph::get_node( std::string name )
	{
		size_t id = 0;

		for (id=0; id < m_vertex.size(); id++)
		{
			if (name == m_vertex[id].name)
				break;
		}

		return m_vertex[id];
	}
	

	

	float Graph::target_distance(int id)
	{
		int parent_edges_size = 0, parent_id = 0 , edge_id = 0;
		float distance = 0;

		while(true){
			parent_id = m_vertex[id].parent_id;

			if (parent_id <= 0)	break;

			parent_edges_size = m_vertex[parent_id].edges.size();

			for (int i = 0; i < parent_edges_size; ++i)
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



     void Graph::write_data(std::string name)
     {
         size_t id;

         for (id; id < m_vertex.size(); id++)
         {
             if (m_vertex[id].name == name)
                 break;
         }

         std::fstream file;
         file.open("destination.txt" , std::ios::out);

         while (true)
         {
             if (id < 0)
                 break;
             file << m_vertex[id].name << " " << m_vertex[id].distance << std::endl;
             id = m_vertex[id].parent_id;
         }

         file.close();
     }
}