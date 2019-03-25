#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <map>


namespace Graph
{
	struct Edge
	{
		int source_id;
		int target_id;
		float distance;
	};

	struct Vertex
	{
		std::string name;
		std::vector <Edge> edges;
		int parent_id = -1;
		bool visited = 0;
	};

	class Graph
	{
	public:
		std::vector <Vertex> m_vertex;

		bool node_exist( std::string name );
		void add_node( std::string name );
		void add_edge( std::string name1, std::string  name2, float dist );
		Vertex get_node( std::string name );
		float target_distance(int id );
		bool is_longer(int id1, int id2, float dist );
	};
}