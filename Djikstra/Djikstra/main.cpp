#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <stdexcept>

#include "Graph.h"

class Arguments
{
public:
    std::string data_file;
    std::string inceptive;
    std::string destination;
    std::string road_file;

    void parse_arguments( char *argv[])
    {
            data_file = argv[1];
            inceptive = argv[2];
            destination = argv[3];
            road_file = argv[4];
    }
};

int main(int argc, char *argv[])
{
    Arguments arguments;
    Graph::Graph graph;
    
    try
    {
        if (argc != 5)
        {
            throw std::invalid_argument("Wrong number of arguments");
        }
    }
    catch (const std::invalid_argument& e)
    {
        std::cout << "Invalid argument: " << e.what() << std::endl;
    }

    arguments.parse_arguments(argv);
    graph.load_graph(arguments.data_file);
    graph.shortest_way(arguments.inceptive, arguments.destination);
    graph.write_data(arguments.destination, arguments.road_file);
    

    system("pause");
    return 0;
}
