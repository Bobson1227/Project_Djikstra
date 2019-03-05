#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct Edge
{
	int 
	int 
	string name; 
	float distance;
};

struct Vertex
{
	string name;
	vector <Edge> edges;
	int parent_id = -1;
	bool visited = 0;
};

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
	
	vector <Vertex> graph;

	while (!file_data.eof())
	{
		file_data >> name1 >> name2 >> dist;
		
		
	}

	cout << name1 << name2 << dist << endl;

	file_data.close();

	system("pause");
	return 0;
}