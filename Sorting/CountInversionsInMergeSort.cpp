/*
	Count Inversions in MergeSort
	
	https://en.wikipedia.org/wiki/Merge_sort
	
	Ashish Sarode 27 July 2018
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

void ReadNumbers(vector<int>& numbers)
{
	ifstream fHandle("C:\\IntegerArray.txt");

	string line;
	while (getline(fHandle, line))
		numbers.push_back(atoi(line.c_str()));
}

long long MergeAndCountInversions(vector<int>& firstHalf, vector<int>& secondHalf, vector<int>& numbers)
{
	long long inversions = 0;
	int lenFirst = firstHalf.size();
	int lenSecond = secondHalf.size();
	for (int i = 0, i1 = 0, i2 = 0; i < numbers.size(); ++i)
	{
		if (i1 == lenFirst)
		{
			numbers[i] = secondHalf[i2];	// Optimization Possible... can be done in single copy command - breaking top for
			i2++;
		}
		else if (i2 == lenSecond)
		{
			numbers[i] = firstHalf[i1];	// Optimization Possible... can be done in single copy command - breaking top for
			i1++;
		}
		else if (firstHalf[i1] <= secondHalf[i2])
		{
			numbers[i] = firstHalf[i1];
			i1++;
		}
		else
		{
			numbers[i] = secondHalf[i2];
			inversions = inversions + (lenFirst - i1);
			i2++;
		}
	}
	return inversions;
}

long long SortAndCountInversions(vector<int>& numbers)
{
	int len = numbers.size();

	if (len == 1)
		return 0;
	else if (len == 2)
	{
		if (numbers[0] <= numbers[1])
			return 0;
		else
		{
			swap(numbers[0], numbers[1]);
			return 1;
		}
	}

	int hlen = len / 2;

	vector<int> firstHalf(numbers.begin(), numbers.begin() + hlen);
	vector<int> secondHalf(numbers.begin() + hlen, numbers.end());

	long long count1 = SortAndCountInversions(firstHalf);
	long long count2 = SortAndCountInversions(secondHalf);
	long long count3 = MergeAndCountInversions(firstHalf, secondHalf, numbers);

	return count1 + count2 + count3;
}

int main()
{
	vector<int> numbers;
	ReadNumbers(numbers);

	long long numInversions = SortAndCountInversions(numbers);

	cout << "Number of Inversions = " << numInversions << endl;

	system("Pause");

	return 0;
}
