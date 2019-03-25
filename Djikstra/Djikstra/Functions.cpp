#include <vector>


#include "Headers.h"


namespace Graph
{
	bool Graph::node_exist( std::string name)
	{
		int i=0, vector_size;
		bool exist = 0;
		vector_size = m_vertex.size();
		
		while ( i < vector_size )
		{
			if (name ==  m_vertex[i].name ) //if name exist break loop, and function
			{
				exist = 1;
				break;
			}
			i++;
		}

		return exist; //if vertex exist, then return 1;
	}



	void Graph::add_node( std::string name)
	{
		int vector_size;

		vector_size = m_vertex.size();

		m_vertex.resize(vector_size + 1 );
		m_vertex[vector_size].name = name;
	}



	void Graph::add_edge( std::string name1, std::string name2, float dist )
	{
		int id1=NULL, id2=NULL, i;
		int vector_size = m_vertex.size();
		int edges_size1, edges_size2;
		//bool h1=0, h2=0;

		for (i = 0; i < vector_size; i++)
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
		int id=0;
		int size = m_vertex.size();
		
		while (id < size)
		{
			if (name == m_vertex[id].name)
			{
				break;
			}
			id++;
		}

		return m_vertex[id];
	}
	

	
	float Graph::target_distance(int id)
	{
		int i = 0, parent_edges_size = NULL, parent_id = NULL , edge_id = NULL;
		float distance = 0;

		// int size = static_cast<int>(m_vertex.size());
		while(1){
			parent_id = m_vertex[id].parent_id; //id rodzica id

			if (parent_id <= 0)	break;

			parent_edges_size = m_vertex[parent_id].edges.size();

			for (i = 0; i < parent_edges_size; i++)
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