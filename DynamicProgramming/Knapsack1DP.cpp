/*
	Knapsack problem solution using Dynamic Programming
	Outputs optimal value of Knapsack.
	
	https://en.wikipedia.org/wiki/Knapsack_problem
	
	Ashish Sarode 12 August 2018
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

void ReadKnapsackData(int& capacity, vector<pair<int, int>>& prValWts)
{
	string line;
	ifstream fHandle("C:\\knapsackTest.txt");

	getline(fHandle, line);
	stringstream strLine(line);
	capacity = -1;
	int numWeights = -1;
	strLine >> capacity >> numWeights;

	prValWts.resize(numWeights+1);
	int val, wt;
	for (int weightIndex = 1; weightIndex <= numWeights; ++weightIndex)
	{
		getline(fHandle, line);
		stringstream strLine(line);
		strLine >> val >> wt;
		prValWts[weightIndex].first = val;
		prValWts[weightIndex].second = wt;
	}
}


int CalculateOptimalKnapsackValue(const int capacity, vector<pair<int, int>>& prValWts)
{
	vector<vector<int>> optimalVals(prValWts.size());
	for (auto& vec : optimalVals)
		vec.resize(capacity+1, 0);

	for (int val = 1; val < prValWts.size(); val++)
	{
		for (int cap = 1; cap <= capacity; cap++)
		{
			const int previousValOptimal = optimalVals[val - 1][cap];
			const int capWithoutCurrentWt = cap - prValWts[val].second;
			const int currentValOptimal = capWithoutCurrentWt < 0 ? 0 :  optimalVals[val-1][capWithoutCurrentWt] + prValWts[val].first;
			optimalVals[val][cap] = max(previousValOptimal, currentValOptimal);
		}
		// cout << val << ": " << optimalVals[val][capacity];
	}
	cout << endl;

	return optimalVals[prValWts.size() - 1][capacity];
}

int main()
{
	int capacity = -1;
	vector<pair<int, int>> prValWts;
	ReadKnapsackData(capacity, prValWts);

	int optimalValue = CalculateOptimalKnapsackValue(capacity, prValWts);
	
	cout << "For given values, weights and capacity, optimal value is  = " << optimalValue << endl;

	system("Pause");

	return 0;
}
