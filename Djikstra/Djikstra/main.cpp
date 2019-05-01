#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>
#include <map>

#include "Graph.h"

class Arguments
{
public:
    std::string data_file;
    std::string inceptive;
    std::string destination;
    std::string road_file;

    void parse_arguments(int argc, char *argv[])
    {
        if (argc != 5)
        {
            std::cout << "Wrong number of arguments" << std::endl;

        }
        else
        {
            data_file = argv[1];
            inceptive = argv[2];
            destination = argv[3];
            road_file = argv[4];
        }
    }
};

int main(int argc, char *argv[])
{
    Arguments arguments;
    Graph::Graph graph;
    arguments.parse_arguments(argc, argv);

    graph.load_graph(arguments.data_file);
    graph.shortest_way(arguments.inceptive, arguments.destination);
    graph.write_data(arguments.destination, arguments.road_file);

    system("pause");
    return 0;
}
