/*
	Prim's algorithm (This is Greedy Algorithm)
	Finds a minimum spanning tree for a weighted unidirected graph
	
	https://en.wikipedia.org/wiki/Prim%27s_algorithm
	
	Ashish Sarode 18 August 2018
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
#include <iterator>
#include <functional>
#include <iomanip>
#include <cmath>


using std::vector;
using std::pair;
using std::priority_queue;
using std::make_pair;

const long HUGE_NUMBER = std::numeric_limits<long>::max();

class PrimsAlgo
{
public:
	PrimsAlgo(vector<int> &x, vector<int> &y);
	~PrimsAlgo();

	double MinimumDistancePathLength();

protected:
	void DetermineMinimumDistancePath();

private:
	vector<pair<int /*x*/, int/*y*/>> mXY;
	vector<pair<int /*parent*/, long /*distance square*/>> mFinalPath;
};

PrimsAlgo::PrimsAlgo(vector<int> &x, vector<int> &y)
{
	size_t sz = x.size();
	std::transform(x.begin(), x.end(), y.begin(), std::back_inserter(mXY), [](int& xx, int& yy) {return make_pair(xx, yy); });
	mFinalPath = std::vector<pair<int, long>>(sz, make_pair(-1, HUGE_NUMBER));
}

PrimsAlgo::~PrimsAlgo()
{

}

double PrimsAlgo::MinimumDistancePathLength()
{
	DetermineMinimumDistancePath();

	double minimumPathLength = 0.0;
	for (auto node : mFinalPath)
	{
		minimumPathLength += sqrt(node.second);
	}

	return minimumPathLength;
}

void PrimsAlgo::DetermineMinimumDistancePath()
{
	int nNode = 0;
	int nNeighbour = 0;
	double distanceSq = 0;
	int nodeX = 0.0;
	int nodeY = 0.0;
	int deltaX = 0.0;
	int deltaY = 0.0;
	pair<long/*Distance*/, pair<int/*Node*/, int/*Parent*/>> topNode;
	
	using nodeType = pair<long, pair<int, int>>;
	priority_queue< nodeType, vector<nodeType>, std::greater<nodeType>> nodeQueue;
	nodeQueue.push(make_pair(0, make_pair(0, 0)));

	int sz = mXY.size();

	while (!nodeQueue.empty())
	{
		topNode = nodeQueue.top();
		nodeQueue.pop();

		nNode = topNode.second.first;

		if (-1 != mFinalPath[topNode.second.first].first)
			continue;
		else
		{
			mFinalPath[nNode].first = topNode.second.second;
			mFinalPath[nNode].second = topNode.first;
		}

		nodeX = mXY[nNode].first;
		nodeY = mXY[nNode].second;
		for (nNeighbour = 0; nNeighbour < sz; nNeighbour++)
		{
			if (nNode == nNeighbour)
				continue;

			if (-1 != mFinalPath[nNeighbour].first)
				continue;

			deltaX = nodeX - mXY[nNeighbour].first;
			deltaY = nodeY - mXY[nNeighbour].second;
			distanceSq = deltaX*deltaX + deltaY*deltaY;

			nodeQueue.push(make_pair(distanceSq, make_pair(nNeighbour, nNode)));
		}
	}
}

double minimum_distance(vector<int> x, vector<int> y) {
	double result = 0.;
	
	//write your code here
	PrimsAlgo objPrimsAlgo(x, y);
	result = objPrimsAlgo.MinimumDistancePathLength();

	return result;
}

int main() {
	size_t n;
	std::cin >> n;
	vector<int> x(n), y(n);
	for (size_t i = 0; i < n; i++) {
		std::cin >> x[i] >> y[i];
	}
	std::cout << std::setprecision(10) << minimum_distance(x, y) << std::endl;
}
