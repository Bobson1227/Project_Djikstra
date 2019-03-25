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
	float dist=0;
	Graph::Graph graph;
	Graph::Vertex node;
	bool end1=0, end2=0;


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

		if (!graph.node_exist(name1 ))
		{
			graph.add_node(name1 );
		}
		if (!graph.node_exist(name2 ))
		{
			graph.add_node(name2 );
		}
		graph.add_edge(name1, name2, dist );
	}

	file_data.close();
	// data loaded


	// searching shortest way from name1 to name2
	std::cout << "From where, to where?" << std::endl;
	std::cin >> name1 >> name2;

	if (!graph.node_exist(name1) )
	{
		std::cout << name1 << " not exist." << std::endl;
		end1 = 1;
	}
	if( !graph.node_exist(name2) )
	{
		std::cout << name2 << " not exist." << std::endl;
		end2 = 1;
	}
	if ( end1 || end2 )
	{
		system("pause");
		exit(1);
	}

	// Checking vertexes
	node = graph.get_node(name1 );
	std::cout << node.name;


	system("pause");
	return 0;
}