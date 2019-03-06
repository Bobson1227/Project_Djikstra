#pragma once

#include <vector>

using namespace std;

namespace graph
{
	class Graph
	{
	private:
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
	public:
		void node_exist( string name);
		void add_node( string name);
		void add_edge( string name1, string  name2, float dist);
		void get_node( string name);
	};
}