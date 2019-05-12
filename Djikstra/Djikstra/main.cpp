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
    Arguments(const char* data_file, const char* source, const char* target, const char* road_file) 
        : data_file(data_file), source(source), target(target), road_file(road_file)
    {};
public:
    const std::string data_file;
    const std::string source;
    const std::string target;
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
    graph.shortest_way(arguments.source, arguments.target);
    graph.write_data(arguments.target, arguments.road_file);
    
    system("pause");
    return 0;
}
