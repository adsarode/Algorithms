/*
	Knapsack problem solution using Dynamic Programming
	Does not store complete table, only uses previous value - requires less memory
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
#include <chrono>

using namespace std;
using namespace std::chrono;

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
	auto start = high_resolution_clock::now();

	vector<int> optimalValCurrent(capacity + 1, 0);
	int optimalVal = 0;
	for (int val = 1; val < prValWts.size(); val++)
	{
		auto optimalValsPrev = optimalValCurrent;

		for (int cap = 1; cap <= capacity; cap++)
		{
			const int previousValOptimal = optimalValsPrev[cap];
			const int capWithoutCurrentWt = cap - prValWts[val].second;
			const int currentValOptimal = capWithoutCurrentWt < 0 ? 0 : optimalValsPrev[capWithoutCurrentWt] + prValWts[val].first;
			optimalValCurrent[cap] = max(previousValOptimal, currentValOptimal);
		}
		// cout << val << ": " << optimalValCurrent[capacity];
		optimalVal = optimalValCurrent[capacity];
	}
	cout << endl;

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<seconds>(stop - start);
	cout << "Time taken by function: "	<< duration.count() << " seconds" << endl;

	return optimalVal;
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
