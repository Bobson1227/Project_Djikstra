#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>
#include <map>

#include "Headers.h"




int main()
{
	std::string name1, name2;
	float dist;
	int i = 0, vector_size;
	bool check_visited;
	Graph::Graph graph;
	Graph::Graph::Vertex node;


	// Loading data
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

		if (!graph.node_exist(name1, graph.m_vertex))
		{
			graph.add_node(name1);
		}
		if (!graph.node_exist(name2, graph.m_vertex))
		{
			graph.add_node(name1);
		}
		graph.add_edge(name1, name2, dist, graph.m_vertex);
	}

	std::cout << name1 << name2 << dist << std::endl;

	file_data.close();

	vector_size = graph.m_vertex.size();

	// Operations
	std::cout << "From where, to where";
	std::cin >> name1 >> name2;

	

	// Checking vertexes
	node = graph.get_node(name1, graph.m_vertex);
	
	i = 0;
	while ( i < vector_size )
	{
		check_visited = 0;

		if (graph.m_vertex[i].visited==0)
		{
			check_visited = 1;
			break;
		}
		
		i++;
	}

	system("pause");
	return 0;
}