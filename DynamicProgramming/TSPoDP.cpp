/*
	Given a list of cities and the distances between each pair of cities.
	Finds the shortest possible route that visits each city
	
	* Note this implementation requires setting 
	N_numBits = Number of cities - 1 (hardcoded value required)
	
	https://en.wikipedia.org/wiki/Travelling_salesman_problem
	
	Another Good read -
	https://medium.com/basecs/the-trials-and-tribulations-of-the-traveling-salesman-56048d6709d
	
	
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
#include <set>
#include <math.h>

#include <chrono>

using namespace std;
using namespace std::chrono;

const int N_numBits = 24;	// Time being this program needs to have hardcoded bit numbers, TODO: check how to make this generic
							// This has to be 1 less than the total number of vertices in TSP
typedef bitset<N_numBits> bitsetN;

struct bitsetNComparator {
	bool operator() (const bitsetN &b1, const bitsetN &b2) const {
		return b1.to_ulong() < b2.to_ulong();
	}
};

class TSPoDPoHeldKarp
{
public:
	TSPoDPoHeldKarp(string path)
		: filePath(path)
	{}

	~TSPoDPoHeldKarp()
	{
		for (int v = 0; v < numVertices; ++v)
		{
			delete[] vertCoords[v];
			delete[] distMatrix[v];
		}

		delete[] vertCoords;
		delete[] distMatrix;
	}

	double Run()
	{
		ReadGraph();
		DefineBitsForVertices();
		double optimalDist = MinimumTSPUsingDP();

		return optimalDist;
	}

	void ReadGraph()
	{
		string line;
		ifstream fHandle(filePath);

		getline(fHandle, line);
		stringstream strLine(line);
		strLine >> numVertices;

		if (N_numBits != numVertices - 1)
		{
			cout << "** Limitation of program, Number of Bits should be set same as numVertices - 1" << endl;
			cout << "** In source file set N_numBits to: " << (numVertices - 1) << endl;
			// exit(1);
		}

		vertCoords = new double*[numVertices];
		for (int v = 0; v < numVertices; ++v)
			vertCoords[v] = new double[2];

		double x, y;
		for (int v = 0; v < numVertices; ++v)
		{
			getline(fHandle, line);
			stringstream strLine(line);
			strLine >> x >> y;

			vertCoords[v][0] = x;
			vertCoords[v][1] = y;
		}


		distMatrix = new double*[numVertices];
		for (int v = 0; v < numVertices; ++v)
			distMatrix[v] = new double[numVertices];

		for (int v1 = 0; v1 < numVertices; ++v1)
		{
			for (int v2 = v1; v2 < numVertices; ++v2)
			{
				x = vertCoords[v1][0] - vertCoords[v2][0];
				y = vertCoords[v1][1] - vertCoords[v2][1];
				distMatrix[v1][v2] = sqrt(x*x + y * y);
				distMatrix[v2][v1] = distMatrix[v1][v2];	// Symmetry
			}
		}
		for (int v1 = 0; v1 < numVertices; ++v1)
			distMatrix[v1][v1] = distMatrix[v1][N_numBits];		// Leafs have to connect to the N th vertex (or last vertex... which will again connect to first)
	}

	void DefineBitsForVertices()
	{
		for (int i = 0; i < N_numBits; ++i)
			bitMap[i] = bitsetN(1 << i);
	}

	double MinimumTSPUsingDP()
	{
		// Starting node is always 0th node, this applies to ending node as well for this it is taken care of by 
		// setting correct distances in diagonal part of dist matrix.

		map<bitsetN, map<int, double>, bitsetNComparator> mapCurrentLevel;
		for (int i = 0; i < N_numBits; ++i)
		{
			mapCurrentLevel[bitMap[i]][i] = distMatrix[i][N_numBits];	// There is cost to adding single vertex to path, since it has to end in vertex 0;
		}

		vector<int> prevVertices;
		double dist = 0.0;
		for (int level = 1; level < N_numBits; level++)
		{
			cout << "Running for Level: " << level << endl;

			// Create map of shortest length for set for given level;
			map<bitsetN, map<int, double>, bitsetNComparator> mapPreviousLevel = mapCurrentLevel;
			mapCurrentLevel.clear();
			for (auto& prevComb : mapPreviousLevel)
			{
				auto complimentComb = ~prevComb.first;

				prevVertices.clear();
				prevVertices.reserve(prevComb.first.count());
				for (int i = 0; i < N_numBits; ++i)
					if (prevComb.first.test(i))
						prevVertices.push_back(i);

				for (int prevV : prevVertices)
				{
					for (int j = 0; j < N_numBits; ++j)
					{
						if (complimentComb.test(j))
						{
							dist = prevComb.second[prevV] + distMatrix[prevV][j];	// TODO: Later remove this temporary to optimize
							auto&& bitN = prevComb.first^bitMap[j];
							auto itr1 = mapCurrentLevel.find(bitN);
							if (itr1 != mapCurrentLevel.end())
							{
								auto itr2 = itr1->second.find(j);
								if (itr2 != itr1->second.end())
									if (dist > itr2->second)
										continue;
							}
							mapCurrentLevel[prevComb.first^bitMap[j]][j] = dist;
						}
					}
				}
			}
		}

		if (1 != mapCurrentLevel.size())
			cout << "??? Error in code : Debug again. mapCurrentLevel should be of size 1 at the end (this last level only connects to all starts)!" << endl;

		double optimalDistance = DBL_MAX;

		for (auto& NthLevelBest : mapCurrentLevel)
		{
			for (auto& best : NthLevelBest.second)
			{
				double distance = best.second + distMatrix[best.first][N_numBits];
				if (optimalDistance > distance)
					optimalDistance = distance;
			}
		}

		return optimalDistance;
	}


protected:

	string filePath;

	int numVertices;
	double **vertCoords;
	double **distMatrix;

	map<int, bitsetN> bitMap;
};


int main()
{
	auto start = high_resolution_clock::now();

	TSPoDPoHeldKarp tspDP(string("C:\\D1\\MOOCs\\Coursera\\AlgorithmsStanford\\04ShortPthNPCProbs\\tsp.txt"));
	double optimalDist = tspDP.Run();

	cout << "Optimal Distance for Travelling Salesman in this case = " << optimalDist << endl;

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<seconds>(stop - start);
	cout << "Time taken by function: " << duration.count() << " seconds" << endl;

	system("Pause");

	return 0;
}
