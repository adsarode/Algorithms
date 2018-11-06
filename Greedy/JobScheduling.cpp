/*
	Job scheduling algorithm
		- Compares weights
		- Compares ratio of weight/ duaration (length)
	
	Ashish Sarode 7 August 2018
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

void ReadJobs(vector<pair<int, int>>& jobs)
{
	string line;
	ifstream fHandle("C:\\jobs.txt");
	getline(fHandle, line);
	jobs.reserve(atoi(line.c_str()));
	while (getline(fHandle, line))
	{
		int weight = -1, length = -1;
		stringstream strLine(line);
		strLine >> weight >> length;

		jobs.push_back(make_pair(weight, length));
	}
}

bool CompareDiffFollwedByWeight(pair<int, int> job1, pair<int, int> job2)
{
	int diff1 = job1.first - job1.second;
	int diff2 = job2.first - job2.second;

	if (diff1 == diff2)
		return (job1.first > job2.first);

	return (diff1 > diff2);
}

bool CompareRatio(pair<int, int> job1, pair<int, int> job2)
{
	double ratio1 = (double)job1.first / (double)job1.second;
	double ratio2 = (double)job2.first / (double)job2.second;

	return ratio1 > ratio2;
}

long long OptimalRunningTimeWithTies(vector<pair<int, int>> jobs, bool (*sortingFn)(pair<int, int> job1, pair<int, int> job2) )
{
	sort(jobs.begin(), jobs.end(), sortingFn);

	long long totalLength = 0;
	long long totalCost = 0.0;
	for (auto job : jobs)
	{
		totalLength = totalLength + job.second;
		totalCost = totalCost + totalLength * job.first;
	}

	return totalCost;
}

int main()
{
	vector<pair<int, int>> jobs;
	ReadJobs(jobs);

	long long cost1 = OptimalRunningTimeWithTies(jobs, CompareDiffFollwedByWeight);
	long long cost2 = OptimalRunningTimeWithTies(jobs, CompareRatio);

	cout << "Total Cost Optimal by Diffeference Resolving Ties Correctly = " << cost1 << endl;
	cout << "Total Cost Optimal by weight = " << cost2 << endl;

	system("Pause");

	return 0;
}
