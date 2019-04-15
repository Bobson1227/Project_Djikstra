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
    Graph::Graph graph;

    graph.load_graph();

    std::cin >> name1 >> name2;
    
    graph.vertexes_exist(name1, name2);
    graph.shortest_way(name1, name2);
    graph.write_data(name2);

    system("pause");
    return 0;
}