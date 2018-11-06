/*
	Finds shortest paths between all pairs of vertices in directed graph
	Detects negative cycle (Uses Bellman-Ford Algorithm for this purpose).
	Uses Dijkstra's algorithm for shortest paths
	
	https://en.wikipedia.org/wiki/Johnson%27s_algorithm
	
	Ashish Sarode 16 August 2018
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

#include <chrono>

using namespace std;
using namespace std::chrono;

const int infinity = 2147483647;

class JonsonAllPathDistances
{
public:
	JonsonAllPathDistances(string path)
		: filePath(path)
	{}

	void Run()
	{
		ReadGraph();
		bool negativeCycle = BellmanFordToAssignVertexWeights(0);

		if (negativeCycle)
			cout << "** Negative cycle detected **" << endl;

		vector<vector<int>> minDistances;
		DijkstraAllShortestPaths(minDistances);
		int minDist = infinity;
		for (int v = 1; v < numVertices; ++v)
		{
			/*cout << v << ": [";
			for (int d = 1; d < minDistances[v].size(); ++d)
				cout << minDistances[v][d] << ",";
			cout << "]" << endl;*/
			for (int d = 1; d < minDistances[v].size(); ++d)
				minDist = min(minDist, minDistances[v][d]);
		}
		if(!negativeCycle)
			cout << "Minimum Distance = " << minDist << endl;
	}

	void ReadGraph()
	{
		string line;
		ifstream fHandle(filePath);

		getline(fHandle, line);
		stringstream strLine(line);
		strLine >> numVertices >> numEdges;
		numVertices++;	// We add one dummy vertex

		edges.reserve(numEdges);
		int from, to, weight;
		for (int edge = 0; edge < numEdges; ++edge)
		{
			getline(fHandle, line);
			stringstream strLine(line);
			strLine >> from >> to >> weight;

			edges.push_back(make_tuple(from, to, weight));
		}

		verticesWeights.resize(numVertices);
	}

	bool BellmanFordToAssignVertexWeights(const int vertexSource)
	{
		vector<tuple<int /*from*/, int /*to*/, int /*weight*/>> dummyEdges = edges;

		for (int v = 0; v < numVertices; ++v)
		{
			dummyEdges.push_back(make_tuple(0, v, 0));
		}


		// We do not create 0 length dummy vertices here, instead just assume that such vertex exists
		vector<int> distances(numVertices, infinity);
		distances[vertexSource] = 0;

		int distance = -1;
		for (int i = 1; i <= numVertices; i++)	// 1 vertex extra because 0th vertex is starting vertex connecting to other vertices with length 0
												// Since the loop is only till n-1, so started from i = 1
		{
			for (auto& edge : dummyEdges)
			{
				if (distances[get<0>(edge)] == infinity)
					continue;

				distance = distances[get<0>(edge)] + get<2>(edge);
				if (distance < distances[get<1>(edge)])
				{
					distances[get<1>(edge)] = distance;
					if (i == numVertices)
						return true;	// Negative cycle
				}
			}
		}

		verticesWeights = distances;
		return false;
	}

	void DijkstraAllShortestPaths(vector<vector<int>>& minDistances)
	{
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> distQueue;

		minDistances.resize(numVertices);
		for (auto& minDists : minDistances)
			minDists.resize(numVertices);

		// Dijkstra algorithm can be coded well if from each vertex we can have the all edges starting from it.
		vector<vector<pair<int, int>>> graph(numVertices);
		int newWeight = -1;	// We need to recompute edge weights based on the Bellman-Ford algorithm detected vertices weights
		for (auto& edge : edges)
		{
			newWeight = get<2>(edge) + verticesWeights[get<0>(edge)] - verticesWeights[get<1>(edge)];
			graph[get<0>(edge)].push_back(make_pair(get<1>(edge), newWeight));
		}

		for (int fromNode = 1; fromNode < numVertices; ++fromNode)
		{
			distQueue.push(make_pair(0, fromNode));
			vector<bool> optimalTracker(numVertices, false);

			/*if (fromNode % 1000 == 0)
				cout << fromNode << "; " << endl;*/

			auto& minDists = minDistances[fromNode];
			while (!distQueue.empty())
			{
				auto optimalNode = distQueue.top();
				distQueue.pop();

				if (optimalTracker[optimalNode.second])	// If the node is already detected as optimal just ignore this
					continue;

				minDists[optimalNode.second] = optimalNode.first - verticesWeights[fromNode] + verticesWeights[optimalNode.second];
				optimalTracker[optimalNode.second] = true;

				for (auto& connection : graph[optimalNode.second])
				{
					if (!optimalTracker[connection.first])	// If the connecting node is already optimal no need to add again
						distQueue.push(make_pair(optimalNode.first + connection.second, connection.first));
				}
			}
		}
	}

protected:

	string filePath;

	int numVertices;
	int numEdges;

	vector<tuple<int /*from*/, int /*to*/, int /*weight*/>> edges;
	vector<int> verticesWeights;
};


int main()
{
	auto start = high_resolution_clock::now();

	JonsonAllPathDistances jonsonAlgo(string("C:\\D1\\MOOCs\\Coursera\\AlgorithmsStanford\\04ShortPthNPCProbs\\large.txt"));
	jonsonAlgo.Run();

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<seconds>(stop - start);
	cout << "Time taken by function: " << duration.count() << " seconds" << endl;

	system("Pause");

	return 0;
}
