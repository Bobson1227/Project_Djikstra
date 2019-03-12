#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <map>


namespace Graph
{
	class Graph
	{
	public:
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

		std::vector <Vertex> m_vertex;

		bool node_exist( std::string name);
		void add_node( std::string name);
		void add_edge( std::string name1, std::string  name2, float dist, std::vector<Graph::Vertex>& vertex);
		Graph::Vertex get_node( std::string name, std::vector<Graph::Vertex>& vertex);
	};
}

// do graph
namespace Operations
{
	float target_distance( int id, std::vector<Graph::Graph::Vertex>& vertex);
	bool is_longer( std::string name, std::vector<Graph::Graph::Vertex>& vertex );
}