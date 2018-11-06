/*
	Given a list of cities and the distances between each pair of cities.
	Finds the shortest possible route that visits each city
	
	This is a heuristic based implementation 
	Heuristics used -
		1. Start the tour with the first city
		2. Repeatedly visitt the closest city that the tour hasn't visited yet.
		In case of tie got to the city with lowest index.
		3. Once every city is visited go back to the starting city.
	
	https://en.wikipedia.org/wiki/Travelling_salesman_problem
	
	Another Good read -
	https://medium.com/basecs/the-trials-and-tribulations-of-the-traveling-salesman-56048d6709d
	
	
	Ashish Sarode 18 August 2018
*/

#include <algorithm>
#include <iterator>
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

class TSPoNearestHeuristic
{
public:
	TSPoNearestHeuristic(const string& path)
		: filePath(path)
	{}

	~TSPoNearestHeuristic()
	{
		for (int city = 0; city < numCities; ++city)
		{
			delete[] cityCoords[city];
		}

		delete[] cityCoords;
	}

	double Run()
	{
		ReadGraph();
		double optimalDist = MinimumTSPUsingNearestHeuristic();

		return optimalDist;
	}

	void ReadGraph()
	{
		string line;
		ifstream fHandle(filePath);

		getline(fHandle, line);
		stringstream strLine(line);
		strLine >> numCities;

		cityCoords = new double*[numCities + 1];	// offset indices by 1
		for (int city = 1; city <= numCities; ++city)
			cityCoords[city] = new double[2];

		int cityNum = 0;
		double x, y;
		for (int city = 1; city <= numCities; ++city)
		{
			getline(fHandle, line);
			stringstream strLine(line);
			strLine >> cityNum >> x >> y;

			/*if (cityNum != city)
				cout << "City numbering order in file assumption failed for city" << city << endl;*/

			cityCoords[city][0] = x;
			cityCoords[city][1] = y;
		}
	}


	double MinimumTSPUsingNearestHeuristic()
	{
		double optimalDistance = 0.0;
		double nearestCityDist2 = DBL_MAX;
		double tempDist2 = 0.0;
		double city1x = 0.0;
		double city1y = 0.0;
		int nearestCity = -1;
		const int numCitiesMinus1 = numCities - 1;

		std::vector<int> cityList;
		int i = 2;	// We dont want to enter 1 st city. We always start from it.
		std::generate_n(inserter(cityList, cityList.begin()), numCities-1, [&i]() { return i++; });
		
		int city1 = 1;
		while (!cityList.empty())
		{
			city1x = cityCoords[city1][0];
			city1y = cityCoords[city1][1];
			nearestCityDist2 = DBL_MAX;

			for (const int& city2 : cityList)
			{
				tempDist2 = pow(city1x - cityCoords[city2][0], 2) + pow(city1y - cityCoords[city2][1], 2);
				if (nearestCityDist2 > tempDist2)
				{
					nearestCityDist2 = tempDist2;
					nearestCity = city2;
				}
			}
			city1 = nearestCity;
			cityList.erase(std::remove(cityList.begin(), cityList.end(), nearestCity), cityList.end());
			optimalDistance += sqrt(nearestCityDist2);

			// cout << nearestCity << " ";
		}

		optimalDistance += sqrt(pow(cityCoords[city1][0] - cityCoords[1][0], 2) + pow(cityCoords[city1][1] - cityCoords[1][1], 2));

		return optimalDistance;
	}


protected:

	string filePath;

	int numCities;
	double **cityCoords;
};


int main()
{
	auto start = high_resolution_clock::now();

	TSPoNearestHeuristic tspNH(string("C:\\TSP.txt"));
	double optimalDist = tspNH.Run();

	cout << "Optimal Distance for Travelling Salesman in this case = " << optimalDist << endl;
	cout << "Optimal Distance for Travelling Salesman in this case = " << (unsigned int)optimalDist << endl;

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<seconds>(stop - start);
	cout << "Time taken by function: " << duration.count() << " seconds" << endl;

	system("Pause");

	return 0;
}
