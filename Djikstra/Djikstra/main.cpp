#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>

#include "Headers.h"

using namespace std;

int main()
{

	string name1, name2;
	float dist;
	int i=0;

	fstream file_data;
	file_data.open("distances.txt", ios::in);

	if (file_data.good() == false)
	{
		cout << "Error with oppening";
		exit(1);
	}
	

	while (!file_data.eof())
	{
		file_data >> name1 >> name2 >> dist;
		
		//if (!graph.node_exists(name1))
		//	graph.add_node(name1);
		//if (!graph.node_exists(name2))
		//	graph.add_node(name2);
		//graph.add_edge(name1, name2, dist);
	}

	cout << name1 << name2 << dist << endl;

	file_data.close();

	system("pause");
	return 0;
}