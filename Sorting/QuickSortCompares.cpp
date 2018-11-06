/*
	Count number of comparisons in QuickSort
	
	https://en.wikipedia.org/wiki/Quicksort
	
	Ashish Sarode 27 July 2018
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// 0 Left Pivot
// 1 Right Pivot
// 2 L R and Mid - whichever comes between two is pivot
// 3 Random number between L and R as pivot
int strategy = 0;

void ReadNumbers(vector<int>& numbers)
{
	ifstream fHandle("C:\\QuickSort.txt");

	string line;
	while (getline(fHandle, line))
		numbers.push_back(atoi(line.c_str()));
}

int DeterminePivot(vector<int>& numbers, const int l, const int r)
{
	if (strategy == 0)
		return l;
	else if (strategy == 1)
		return r;
	else if (strategy == 2)
	{
		int numl = numbers[l];
		int numr = numbers[r];
		int mid = (l + r) / 2;
		int numm = numbers[mid];

		vector<int> keyNums;
		keyNums.push_back(numl);
		keyNums.push_back(numr);
		keyNums.push_back(numm);
		std::sort(keyNums.begin(), keyNums.end());

		if (numl == keyNums[1])
			return l;
		else if (numr == keyNums[1])
			return r;
		else // if (numm == keyNums[1])
			return mid;
	}

	return std::rand() % (max(r, l) - min(r, l)) + min(r, l);
}

long long QuickSortAndCountComparision(vector<int>& numbers, const int l, const int r)
{
	if (r - l < 1)
		return 0;

	// Keep the pivot at the l index
	int pivot = DeterminePivot(numbers, l, r);
	std::swap(numbers[l], numbers[pivot]);

	int i = l + 1;
	for (int j = l + 1; j <= r; ++j)
	{
		if (numbers[j] <= numbers[l])
		{
			swap(numbers[j], numbers[i]);
			i = i + 1;
		}
	}
	swap(numbers[l], numbers[i - 1]);

	long long numSwapsL = QuickSortAndCountComparision(numbers, l, i - 2);
	long long numSwapsR = QuickSortAndCountComparision(numbers, i, r);

	long long numSwaps = long long(r - l) + numSwapsL + numSwapsR;

	return numSwaps;
}

int main()
{
	vector<int> numbers;
	ReadNumbers(numbers);

	strategy = 3;
	long long numCompares = QuickSortAndCountComparision(numbers, 0, numbers.size() - 1);
	cout << "Number of Comparisons Start Strategy " << strategy << " = " << numCompares << endl;

	system("Pause");

	return 0;
}