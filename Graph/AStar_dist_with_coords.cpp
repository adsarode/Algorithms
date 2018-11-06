/*
	A* algorithm (This is Greedy Algorithm)
	Better performance compared to Dijkstra
	
	https://en.wikipedia.org/wiki/A*_search_algorithm
	
	Ashish Sarode 18 August 2018
*/

#include <cstdio>
#include <cassert>
#include <vector>
#include <queue>
#include <limits>
#include <utility>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <functional>

using namespace std;

// See the explanations of these typedefs and constants in the starter for friend_suggestion
typedef vector<vector<vector<int>>> Adj;
typedef long long Len;
typedef vector<priority_queue<pair<Len, int>, vector<pair<Len, int>>, greater<pair<Len, int>>>> Queue;

const Len INFINITE_LEN = numeric_limits<Len>::max() / 4;

const int front = 0;
const int back = 1;

class AStar {
	// See the descriptions of these fields in the starter for friend_suggestion
	int n_;
	Adj adj_;
	Adj cost_;
	vector<vector<Len>> distance_;
	vector<int> workset_;
	vector<bool> visited_;
	vector<vector<bool>> optimalNodes_;
	// Coordinates of the nodes
	std::vector<std::pair<Len, Len>> xy_;
	std::vector<Len> potentials_;
	int start_;
	int target_;

public:
	AStar(int n, Adj adj, Adj cost, std::vector<std::pair<Len, Len>> xy)
		: n_(n),
		adj_(adj), cost_(cost),
		distance_(2, vector<Len>(n_, INFINITE_LEN)),
		visited_(n),
		xy_(xy),
		optimalNodes_(2, vector<bool>(n)),
		potentials_(n_, 0)
	{
		workset_.reserve(n);
	}

	// See the description of this method in the starter for friend_suggestion
	void clear() {
		int worksetSz = workset_.size();
		for (int i = 0; i < worksetSz; ++i) {
			int v = workset_[i];
			distance_[0][v] = distance_[1][v] = INFINITE_LEN;
			optimalNodes_[0][v] = optimalNodes_[1][v] = visited_[v] = false;
			potentials_[v] = 0;
		}
		workset_.clear();
	}

	// See the description of this method in the starter for friend_suggestion
	void visit(Queue& q, int side, int v) {
		// Implement this method yourself
		int nodeIndex = 0;
		int nodeId = 0;
		int adjSz = adj_[side][v].size();
		Len targetDist;
		Len sourceDist;
		for (nodeIndex = 0; nodeIndex < adjSz; ++nodeIndex)
		{
			nodeId = adj_[side][v][nodeIndex];
			if (!visited_[nodeId])
			{
				visited_[nodeId] = true;
				workset_.push_back(nodeId);
				targetDist = sqrt(pow((xy_[target_].first - xy_[nodeId].first), 2) +
								  pow((xy_[target_].second - xy_[nodeId].second), 2));

				sourceDist = sqrt(pow((xy_[start_].first - xy_[nodeId].first), 2) +
								  pow((xy_[start_].second - xy_[nodeId].second), 2));

				potentials_[nodeId] = (targetDist - sourceDist) / 2;
			}
			if (distance_[side][nodeId] > (distance_[side][v] + cost_[side][v][nodeIndex]))
			{
				distance_[side][nodeId] = (distance_[side][v] + cost_[side][v][nodeIndex]);
				q[side].push(make_pair(distance_[side][nodeId] + ((side == front) ? potentials_[nodeId] : -potentials_[nodeId]), nodeId));
			}
		}
	}

	// Returns the distance from s to t in the graph
	Len query(int s, int t) {
		if (s == t)
			return 0;

		start_ = s;
		target_ = t;

		clear();

		workset_.push_back(s);
		visited_[s] = true;

		workset_.push_back(t);
		visited_[t] = true;

		int nodePopped[2] = { s, t };
		Len nodeDistance[2] = { 0, 0 };

		int meetupNodeId = -1;
		Len optimalDistance = INFINITE_LEN;

		Queue q(2);
		distance_[front][s] = 0;
		distance_[back][t] = 0;
		q[0].push(make_pair(0, s));
		visit(q, front, s);
		q[1].push(make_pair(0, t));
		visit(q, back, t);

		// Implement the rest of the algorithm yourself
		while (!q[front].empty() || !q[back].empty())
		{
			if (!q[front].empty())
			{
				nodePopped[front] = q[front].top().second;
				nodeDistance[front] = q[front].top().first;
				q[front].pop();
				optimalNodes_[front][nodePopped[front]] = true;
				if (optimalNodes_[back][nodePopped[front]])	//	If the node is already visited. Then it means that backward search has already found it
				{
					meetupNodeId = nodePopped[front];
					optimalDistance = distance_[front][meetupNodeId] + distance_[back][meetupNodeId];
					break;
				}
				if (!optimalNodes_[back][nodePopped[front]])
					visit(q, front, nodePopped[front]);
			}

			if (!q[back].empty())
			{
				nodePopped[back] = q[back].top().second;
				nodeDistance[back] = q[back].top().first;
				q[back].pop();
				optimalNodes_[back][nodePopped[back]] = true;
				if (optimalNodes_[front][nodePopped[back]])	//	If the node is already visited. Then it means that forward search has already found it
				{
					meetupNodeId = nodePopped[back];
					optimalDistance = distance_[front][meetupNodeId] + distance_[back][meetupNodeId];
					break;
				}
				if (!optimalNodes_[front][nodePopped[back]])
					visit(q, back, nodePopped[back]);
			}
		}

		if (-1 != meetupNodeId)
		{
			int nVizSz = visited_.size();

			for (int nodeIndex = 0; nodeIndex < nVizSz; nodeIndex++)
			{
				if (visited_[nodeIndex])
				{
					if (optimalDistance > distance_[0][nodeIndex] + distance_[1][nodeIndex])
					{
						optimalDistance = distance_[0][nodeIndex] + distance_[1][nodeIndex];
					}
				}
			}

			return optimalDistance;
		}

		return -1;
	}
};

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	std::vector<std::pair<Len, Len>> xy(n);
	for (int i = 0; i<n; ++i){
		int a, b;
		scanf("%d%d", &a, &b);
		xy[i] = make_pair(a, b);
	}
	Adj adj(2, vector<vector<int>>(n));
	Adj cost(2, vector<vector<int>>(n));
	for (int i = 0; i<m; ++i) {
		int u, v, c;
		scanf("%d%d%d", &u, &v, &c);
		adj[0][u - 1].push_back(v - 1);
		cost[0][u - 1].push_back(c);
		adj[1][v - 1].push_back(u - 1);
		cost[1][v - 1].push_back(c);
	}

	AStar astar(n, adj, cost, xy);

	int t;
	scanf("%d", &t);
	for (int i = 0; i<t; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		printf("%lld\n", astar.query(u - 1, v - 1));
	}
}
