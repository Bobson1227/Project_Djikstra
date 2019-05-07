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
    Arguments(const char* data_file, const char* inceptive, const char* destination, const char* road_file) 
        : data_file(data_file), inceptive(inceptive), destination(destination), road_file(road_file)
    {};
public:
    const std::string data_file;
    const std::string inceptive;
    const std::string destination;
    const std::string road_file;

    static Arguments parse_arguments( int argc, char *argv[])
    {
        if (argc != 5)
        {
            throw std::invalid_argument("Wrong number of arguments");
        }

        return Arguments(argv[1], argv[2], argv[3], argv[4]);
    }
};

int main(int argc, char *argv[])
{
    Arguments arguments = Arguments::parse_arguments(argc, argv);
    Graph::Graph graph;
    
    
        arguments.parse_arguments(argc, argv);
        graph.load_graph(arguments.data_file);
        graph.shortest_way(arguments.inceptive, arguments.destination);
        graph.write_data(arguments.destination, arguments.road_file);
    
    

    

    system("pause");
    return 0;
}
