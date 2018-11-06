/*
	Merge sort algorithm
	Counts and outputs the number of inversions
	
	https://en.wikipedia.org/wiki/Karger%27s_algorithm
	
	Ashish Sarode 27 July 2018
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <map>
using namespace std;

void ReadGraph(map<int, vector<int>>& nodesAndEdges)
{
	ifstream fHandle("C:\\kargerMinCut.txt");

	const char input_delimiter = '\t';
	string input_string;
	cout << "Input space delimited series of integers" << endl;
	while (getline(fHandle, input_string))
	{
		stringstream input_parser_stream(input_string);
		vector<string> parsed_input;
		for (string input_element;
			getline(input_parser_stream, input_element, input_delimiter);
			parsed_input.push_back(input_element));

		int index = atoi(parsed_input[0].c_str());
		for (int i = 1; i < parsed_input.size(); ++i)
		{
			nodesAndEdges[index].push_back(atoi(parsed_input[i].c_str()));
		}
	}
}

int GetRandom(const int min, const int max)
{
	return (rand() % (max - min) + min);
}

int kargersMinCutAlgorithm(map<int, vector<int>> nodesAndEdges, int& node1, int& node2)
{
	// Get all keys in map
	vector<int> keys(nodesAndEdges.size());
	int  i = 0;
	for (const auto itr : nodesAndEdges)
		keys[i++] = itr.first;

	while (nodesAndEdges.size() > 2)
	{
		// Pick random u
		int node1keyIndex = GetRandom(0, keys.size() - 1);
		node1 = keys[node1keyIndex];

		// Pick random edge connecting u to some random v
		int edgeIndex = GetRandom(0, nodesAndEdges[node1].size() - 1);
		auto& node1Edges = nodesAndEdges[node1];
		node2 = node1Edges[edgeIndex];

		// Delete edge Edge - Remove edges from noth node edge list... no question of loops then
		node1Edges.erase(remove(node1Edges.begin(), node1Edges.end(), node2), node1Edges.end());
		auto& node2Edges = nodesAndEdges[node2];
		node2Edges.erase(remove(node2Edges.begin(), node2Edges.end(), node1), node2Edges.end());

		node1Edges.reserve(node1Edges.size() + node2Edges.size());
		// node1Edges.insert(node1Edges.end(), node2Edges.begin(), node2Edges.end());
		for (auto node : node2Edges)
		{
			node1Edges.push_back(node);
			std::replace(nodesAndEdges[node].begin(), nodesAndEdges[node].end(), node2, node1);
		}

		// Erase node2 from map
		auto itNode2 = nodesAndEdges.find(node2);
		nodesAndEdges.erase(itNode2);
		// Erase node2 key from keys vector
		keys.erase(remove(keys.begin(), keys.end(), node2), keys.end());
	}

	return nodesAndEdges[keys[0]].size();
}

int main()
{
	map<int, vector<int>> nodesAndEdges;
	ReadGraph(nodesAndEdges);
	vector<int> minCut;
	for (int i = 1; i <= 25; ++i)
	{
		int node1 = -1, node2 = -1;
		int minCutSize = kargersMinCutAlgorithm(nodesAndEdges, node1, node2);
		minCut.push_back(minCutSize);
		cout << "Iteration : " << i << " Node1 : " << node1 << " Node2 : " << node2 << " MinCutSize : " << minCutSize << endl;
	}

	ofstream fHandle("C:\\MinimumCuts.txt");
	for (auto val : minCut)
		fHandle << val << endl;
	fHandle << "Minimum Cut : " << *min_element(minCut.begin(), minCut.end()) << endl;
	system("Pause");

	return 0;
}