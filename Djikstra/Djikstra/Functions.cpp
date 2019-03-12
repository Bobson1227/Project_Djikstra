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
			if (name ==  m_vertex[i].name ) //if name exist break loop and continue
			{
				exist = 1;
				break;
			}

			i++;
		}

		return exist; //if vertex exist - return 1;
	}


	void add_node( std::string name, std::vector<Graph::Vertex>& vertex )
	{
		int vector_size;
			
		vector_size = vertex.size() + 1;

		vertex.resize(vector_size);
		vertex[vector_size - 1].name = name;
	}


	void add_edge( std::string name1, std::string name2, float dist, std::vector<Graph::Vertex>& vertex )
	{
		int id, i;
		int vector_size = vertex.size();
		int edges_size;
		bool h1=0, h2=0;

		for (id = 0; id < vector_size; id++)
		{
			edges_size = vertex[id].edges.size();

			if (vertex[id].name == name1)
			{
				vertex[id].edges.resize(edges_size + 1);

				for (i = 0; name2 != vertex[i].name; i++)
				{

				}

				vertex[id].edges[edges_size].source_id = id;
				vertex[id].edges[edges_size].target_id = i;
				vertex[id].edges[edges_size].distance = dist;
			}
			else if (vertex[id].name == name2)
			{
				vertex[id].edges.resize(edges_size + 1);

				for (i = 0; name1 != vertex[i].name; i++)
				{

				}
				
				vertex[id].edges[edges_size].source_id = id;
				vertex[id].edges[edges_size].target_id = i;
				vertex[id].edges[edges_size].distance = dist;
			}

			if (h1 && h2 )
			{
				break;
			}
		}
	}


	Graph::Vertex get_node( std::string name, std::vector<Graph::Vertex>& vertex )
	{
		int id=0;
		int size = vertex.size();
		for (id = 0; id < size; id++)
		{
			if (name == vertex[id].name)
				break;
		}

		return vertex[id];
	}
}


namespace Operations
{
	float target_distance( int id, std::vector<Graph::Graph::Vertex>& vertex)
	{
		int i, edges_size;
		float distance=0;
		int parent_id, edge_id, accessory_id;
		// id = vertex, do którego szukamy dystansu

		parent_id = vertex[id].parent_id; //id rodzica id
		edges_size = vertex[parent_id].edges.size(); //rozmiar egdes rodzica

		for (i=0; i < edges_size ; i++) // sprawdzanie wszystkich edges rodzica
		{
			if ( id == vertex[parent_id].edges[i].target_id ) 
			{
				edge_id = i;
				break;
			}

		}

		distance += vertex[parent_id].edges[edge_id].distance;

		//accessory_id = vertex[parent_id].edges[i];

		// dodawac do distance odleglosci do naszego vertexa od jego "rodzica"

		return distance;
	}

	bool is_longer( std::string name, std::vector<Graph::Graph::Vertex>& vertex )
	{
		bool longer = 0;
		//sfloat dist_source, dist_target, dist;
		int id=0, vector_size;
		vector_size = vertex.size();

		// pobranie wartosci dist_source, dist_target, dist
		// sprawdzenie, czy distsource+dist < dist
		// jesli jest > zwraca longer=1;

		for (id = 0; id < vector_size; id++)
		{
			if (name == vertex[id].name)
			{
				break;
			}
		}
		
		
		
		return longer;
	}
}