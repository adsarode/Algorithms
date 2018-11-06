/*
	Maximum Weight Independent Set using Dynamic Programming
	
	https://en.wikipedia.org/wiki/Independent_set_(graph_theory)
	
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

void ReadWeights(vector<int>& weights)
{
	string line;
	ifstream fHandle("C:\\mwisTest.txt");

	getline(fHandle, line);
	stringstream strLine(line);
	int totalWeights = -1;
	strLine >> totalWeights;

	weights.resize(totalWeights + 1, 0);	// Number 0 is purposefully kept 0
	for (int weightIndex = 1; weightIndex <= totalWeights; ++weightIndex)
	{
		getline(fHandle, line);
		weights[weightIndex] = stoi(line);
	}
}

void MaxWeightIndependentSet(vector<int>& weights, vector<bool>& selectedVertices)
{
	vector<long long> maxSums(weights.size());
	maxSums[0] = 0;
	maxSums[1] = weights[1];
	for (int i = 2; i < maxSums.size(); ++i)
	{
		maxSums[i] = max(maxSums[i - 1], maxSums[i - 2] + (long long)weights[i]);
	}

	int i = -1;
	for (i = maxSums.size() - 1; i > 1; /*--i*/)
	{
		if (maxSums[i - 1] >= maxSums[i - 2] + (long long)weights[i])
		{
			i--;
		}
		else
		{
			selectedVertices[i] = true;
			i = i - 2;
		}
	}
	if (selectedVertices[3])	// If last vertex added was 3 then our for loop will terminate and will not run for i == 2 and i
		selectedVertices[1] = true;
}

int main()
{
	vector<int> weights;
	ReadWeights(weights);

	vector<bool> selectedVertices(weights.size(), false);
	MaxWeightIndependentSet(weights, selectedVertices);

	vector<int> weightsOfInterest = {1,2,3,4,17,117,517,997};

	for (int index : weightsOfInterest)
	{
		cout << index << " : " << selectedVertices[index] << endl;
	}

	system("Pause");

	return 0;
}
