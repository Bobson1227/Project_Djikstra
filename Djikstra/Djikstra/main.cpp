#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>
#include <map>

#include "Graph.h"


int main()
{
	std::string name1, name2;
	bool end1=0, end2=0;
	Graph::Graph graph;
	Graph::Vertex node;

	graph.load_graph();


	// searching shortest way from name1 to name2
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

     graph.shortest_way(name1, name2);
     graph.write_data(name2);


	system("pause");
	return 0;
}