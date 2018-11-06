/*
	Kruskal's algorith is a minimum spanning tree algorithm which finds an edge of least
	possible weight that connects any two tress in the forest
	
	https://en.wikipedia.org/wiki/Kruskal%27s_algorithm
	
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

int numV = -1;
int numE = -1;

using edge = tuple<int, int, int>;

void ReadGraph(vector<vector<pair<int,int>>>& graph)	// Vector Index is From Node Vector of ToNode, weight pair
{
	string line;
	ifstream fHandle("C:\\clustering1Test.txt");
	
	getline(fHandle, line);
	stringstream strLine(line);
	strLine >> numV;

	graph.resize(numV+1);
	while (getline(fHandle, line))
	{
		int fromNode = -1, toNode = -1, dist = -1;
		stringstream strLine(line);
		strLine >> fromNode >> toNode >> dist;

		graph[fromNode].push_back(make_pair(toNode, dist));
		numE++;
	}
}

int KruskalsAlgorithm(vector<vector<pair<int, int>>>& graph, 
					  const int finalClusters)
{
	vector<tuple<int, int, int>> sortedEdges;
	sortedEdges.reserve(numE);	// Does not need first offset entry
	for (int i = 1; i < graph.size(); ++i)
	{
		for (auto& edge : graph[i])
		{
			sortedEdges.push_back(make_tuple(edge.second, i, edge.first));
		}
	}
	sort(sortedEdges.begin(), sortedEdges.end());

	int numClusters = numV;
	vector<pair<int, int>> clusterRank(numV + 1);	// Vector of Parent, Rank

	for (int node = 0; node <= numV; ++node)
	{
		clusterRank[node] = make_pair(node, 0);		// In the beginning node is parent of itself
	}

	int minDistance = -1;
	int edgeIndex = 0;
	int numEdges = sortedEdges.size();
	while (numClusters >= finalClusters && (edgeIndex != numEdges))
	{
		auto& edge = sortedEdges[edgeIndex++];
		minDistance = get<0>(edge);

		const int& node1 = get<1>(edge);
		const int& node2 = get<2>(edge);

		int parent1 = node1;
		stack<int> parentsNode1;
		parentsNode1.push(node1);

		while (!parentsNode1.empty())
		{
			if (parentsNode1.top() == clusterRank[parentsNode1.top()].first)
			{
				parent1 = parentsNode1.top();
				parentsNode1.pop();
				while (!parentsNode1.empty())
				{
					clusterRank[parentsNode1.top()].first = parent1;
					parentsNode1.pop();
				}
			}
			else
				parentsNode1.push(clusterRank[parentsNode1.top()].first);
		}
		int parent2 = node2;
		stack<int> parentsNode2;
		parentsNode2.push(node2);
		while (!parentsNode2.empty())
		{
			if (parentsNode2.top() == clusterRank[parentsNode2.top()].first)
			{
				parent2 = parentsNode2.top();
				parentsNode2.pop();
				while (!parentsNode2.empty())
				{
					clusterRank[parentsNode2.top()].first = parent2;
					parentsNode2.pop();
				}
			}
			else
				parentsNode2.push(clusterRank[parentsNode2.top()].first);
		}

		if (parent1 == parent2)
			continue;

		if (clusterRank[parent1].second == clusterRank[parent2].second)
		{
			clusterRank[parent1].second = clusterRank[parent1].second + 1;
			clusterRank[parent2].first = clusterRank[parent1].first;
		}
		else if (clusterRank[parent1].second >= clusterRank[parent2].second)
		{
			clusterRank[parent2].first = clusterRank[parent1].first;
		}
		else
			clusterRank[parent1].first = clusterRank[parent2].first;

		numClusters--;
	}

	return minDistance;
}

int main()
{
	vector<vector<pair<int, int>>> graph;
	ReadGraph(graph);
	
	const int numClusters = 4;
	int minSpacing = KruskalsAlgorithm(graph, numClusters);

	cout << "Minimum Spacing required for " << numClusters << " clusters = " << minSpacing << endl;

	system("Pause");
	
	return 0;
}
