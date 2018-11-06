/*
	Prim's greedy algorithm for minimum spanning tree
	Print's overall cost of MST
		
	https://en.wikipedia.org/wiki/Prim%27s_algorithm
	
	Ashish Sarode 9 August 2018
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

void ReadGraph(vector<vector<pair<int, int>>>& graph)	// Vector Index is From Node Vector of ToNode, weight pair
{
	string line;
	ifstream fHandle("C:\\edgesTest2.txt");

	getline(fHandle, line);
	int numV = -1, numE = -1;
	stringstream strLine(line);
	strLine >> numV >> numE;

	graph.resize(numV + 1);
	while (getline(fHandle, line))
	{
		int fromNode = -1, toNode = -1, dist = -1;
		stringstream strLine(line);
		strLine >> fromNode >> toNode >> dist;

		graph[fromNode].push_back(make_pair(toNode, dist));
	}
}

void PrimsAlgorithm(const int fromNode,
	vector<vector<pair<int, int>>>& graph,
	vector<int>& minEdge)
{
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> distQueue;

	distQueue.push(make_pair(0, fromNode));
	vector<bool> optimalTracker(graph.size(), false);
	minEdge.resize(graph.size());

	while (!distQueue.empty())
	{
		auto optimalNode = distQueue.top();
		distQueue.pop();

		if (optimalTracker[optimalNode.second])	// If the node is already detected as optimal just ignore this
			continue;

		minEdge[optimalNode.second] = optimalNode.first;
		optimalTracker[optimalNode.second] = true;

		for (auto connection : graph[optimalNode.second])
		{
			if (!optimalTracker[connection.first])	// If the connecting node is already optimal no need to add again
				distQueue.push(make_pair(connection.second, connection.first));
		}
	}
}

int main()
{
	vector<vector<pair<int, int>>> graph;
	ReadGraph(graph);

	const int fromNode = 1;
	vector<int> minEdges;
	PrimsAlgorithm(fromNode, graph, minEdges);

	int totalCost = 0;
	for (int node = 1; node < minEdges.size(); node++)
	{
		totalCost = totalCost + minEdges[node];
	}

	cout << "Overall Cost of Minimum Spanning Tree (Prim's Algorithm) = " << totalCost << endl;

	system("Pause");

	return 0;
}
