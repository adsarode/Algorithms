/*
	Dijkstra's shortest path Algorithm
	
	https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
	
	Ashish Sarode 6 August 2018
*/


#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stack>
#include <map>
#include <queue>
#include <fstream>
#include <functional>
using namespace std;

void ReadGraph(vector<vector<pair<int,int>>>& graph)	// Vector Index is From Node Vector of ToNode, weight pair
{
	ifstream fHandle("C:\\dijkstraData.txt");

	int numNodes = 0;
	cout << "Enter the number of nodes in graph : ";
	cin >> numNodes;
	cout << endl;
	graph.resize(numNodes + 1);

	const char delimiter1 = '\t';
	string line;
	while (getline(fHandle, line))
	{
		stringstream lineParser(line);
		vector<string> nodeDistPairs;
		for (string pairs;
			getline(lineParser, pairs, delimiter1);
			nodeDistPairs.push_back(pairs));

		int fromNode = atoi(nodeDistPairs[0].c_str());
		for (int i = 1; i < nodeDistPairs.size(); ++i)
		{
			int toNode = 0;
			char comma;
			int weight = 0;

			stringstream strPair(nodeDistPairs[i]);

			strPair >> toNode >> comma >> weight;

			graph[fromNode].push_back(make_pair(toNode, weight));
		}
	}

	cout << "**  Input Reading Complete  **";
}

void DijkstrasAlgorithm(const int fromNode,
						vector<vector<pair<int, int>>>& graph, 
						vector<int>& minDistances)
{
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> distQueue;

	distQueue.push(make_pair(0, fromNode));
	vector<bool> optimalTracker(graph.size(), false);
	minDistances.resize(graph.size());

	while (!distQueue.empty())
	{
		auto optimalNode = distQueue.top();
		distQueue.pop();

		if (optimalTracker[optimalNode.second])	// If the node is already detected as optimal just ignore this
			continue;

		minDistances[optimalNode.second] = optimalNode.first;
		optimalTracker[optimalNode.second] = true;

		for (auto& connection : graph[optimalNode.second])
		{
			if(!optimalTracker[connection.first])	// If the connecting node is already optimal no need to add again
				distQueue.push(make_pair(optimalNode.first + connection.second, connection.first));
		}
	}
}

int main()
{
	vector<vector<pair<int, int>>> graph;
	ReadGraph(graph);
	
	const int fromNode = 1;
	vector<int> minDistances;
	DijkstrasAlgorithm(fromNode, graph, minDistances);

	vector<int> questionNodes = { 7,37,59,82,99,115,133,165,188,197 };

	for (int node : questionNodes)
	{
		cout << node << ":" << minDistances[node] << "; ";
	}

	system("Pause");
	
	return 0;
}
