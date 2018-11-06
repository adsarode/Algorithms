/*
	Kruskal's algorith is a minimum spanning tree algorithm which finds an edge of least
	possible weight that connects any two tress in the forest
	
	This implementation uses Union Find (24 hard coded bits)
	Note, this implementation requires setting 64 bit configuration.
	At peak it consumes around 6GB of ram and run for around hanf and hour
	
	https://en.wikipedia.org/wiki/Kruskal%27s_algorithm
	
	Ashish Sarode 18 August 2018
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
#include <bitset>

using namespace std;

int numV = -1;
int numBits = -1;

using edge = tuple<int, int, int>;

void ReadGraph(vector<int>& nodeBitsGraph)	// Vector Index is From Node Vector of ToNode, weight pair
{
	string line;
	ifstream fHandle("C:\\clustering2Test.txt");

	getline(fHandle, line);
	stringstream strLine(line);
	strLine >> numV >> numBits;

	nodeBitsGraph.resize(numV + 1);
	int nodeIndex = 1;
	while (getline(fHandle, line))
	{
		line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
		nodeBitsGraph[nodeIndex++] = stoi(line, nullptr, 2);
	}
}

int KruskalsAlgorithm(vector<int>& nodeBitsGraph,
	const int minClusterSpacing)
{
	int numClusters = numV;
	vector<pair<int, int>> clusterRank(numV + 1);	// Vector of Parent, Rank

	for (int node = 0; node <= numV; ++node)
	{
		clusterRank[node] = make_pair(node, 0);		// In the beginning node is parent of itself
	}

	for (int node1 = 1; node1 < numV; node1++)
	{
		if (node1 % 10000 == 0)
			cout << node1 << "; " << endl;

		for (int node2 = node1 + 1; node2 <= numV; node2++)
		{
			int distance = nodeBitsGraph[node1] ^ nodeBitsGraph[node2]; // XOR
			bitset<24> dist(distance);
			int bitCount = dist.count(); //  bitCount2(distance);

			if (bitCount < minClusterSpacing)
			{
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
		}
	}

	return numClusters;
}

int main()
{
	vector<int> nodeBitsGraph;
	ReadGraph(nodeBitsGraph);

	const int minClusterSpacing = 3;

	int numberOfClusters = KruskalsAlgorithm(nodeBitsGraph, minClusterSpacing);

	cout << "With MinimumSpacing as " << minClusterSpacing << " clusters size = " << numberOfClusters << endl;

	system("Pause");

	return 0;
}
