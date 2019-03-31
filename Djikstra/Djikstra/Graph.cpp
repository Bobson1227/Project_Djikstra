#include <vector>
#include <queue>
#include <deque>
#include <map>
#include <fstream>
#include <string>

#include "Graph.h"

// nie trzeba wrzucic do class Graph, zeby vector byl widoczny?
class Comparator {
public:
	
};



namespace Graph
{
	bool Graph::node_exist( std::string name)
	{
		for (size_t i = 0; i < m_vertex.size(); i++)
		{
			if (name == m_vertex[i].name) //if name exist break loop, and function
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
		int id1=NULL, id2=NULL;
		int edges_size1, edges_size2;
		//bool h1=0, h2=0;

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
	

	
	Vertex Graph::get_node( std::string name )
	{
		size_t id = 0;

		for (id=0; id < m_vertex.size(); id++)
		{
			if (name == m_vertex[id].name) //if name exist break loop, and function
				break;
		}

		return m_vertex[id];
	}
	

	
	float Graph::target_distance(int id)
	{
		int parent_edges_size = NULL, parent_id = NULL , edge_id = NULL;
		float distance = 0;

		// int size = static_cast<int>(m_vertex.size());
		while(1){
			parent_id = m_vertex[id].parent_id; //id rodzica id

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
	

	bool Graph::is_longer(int id1, int id2, float dist )
	{
		bool longer = 0;

		if (target_distance(id1) + dist > target_distance(id2))
			longer = 1;

		return longer; // if longer, then return 1
	}
}