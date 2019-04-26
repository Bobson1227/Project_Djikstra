#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>
#include <map>

#include "Graph.h"

int main(int argc, char *argv[])
{
    if (argc == 2){
        std::string name1 = argv[0], name2 = argv[1];
        Graph::Graph graph;

        graph.load_graph();
        graph.vertexes_exist(name1, name2);
        graph.shortest_way(name1, name2);
        graph.write_data(name2);
    }
    else
        std::cout << "Passed wrong number of arguments" << std::endl;

    system("pause");
    return 0;
}