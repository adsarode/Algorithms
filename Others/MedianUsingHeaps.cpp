/*
	Algorithm using Min and Max heap to maintain Medican of given numbers
	O(log(i)) time at each step i
	
	Print sum of the running medians
	
	Ashish Sarode 6 August 2018
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

class heap
{
private:
	
	bool(*comparator) (int left, int right);
	vector<int> heapData;

	int parent(int index)
	{
		if (index == 0)
			return -1;

		return (index - 1) / 2;
	}

	int leftChild(int parentIndex)
	{
		int left = parentIndex * 2 + 1;

		if (left < heapData.size())
			return left;

		return -1;
	}

	int rightChild(int parentIndex)
	{
		int right = parentIndex * 2 + 2;
		if (right < heapData.size())
			return right;

		return -1;
	}

public:
	heap(bool(*f) (int left, int right))
		: comparator(f)
	{
	}
	~heap() {};

	int top() { return heapData[0]; };

	int size() { return heapData.size(); }

	void insert(const int val) 
	{
		heapData.push_back(val);
		int insertedIndex = heapData.size() - 1;
		int parentIndex = parent(heapData.size() - 1);
		while (parentIndex != -1)
		{
			if (!comparator(val, heapData[parentIndex]))
			{
				break;
			}
			else
			{
				swap(heapData[insertedIndex], heapData[parentIndex]);
				insertedIndex = parentIndex;
				parentIndex = parent(parentIndex);
			}
		}
	}

	int pop()
	{
		if (heapData.empty())
			return -1;

		int top = heapData.front();
		heapData[0] = heapData[heapData.size() - 1];
		heapData.pop_back();
		int position = 0;
		while (true)
		{
			int optimal = position;
			int left = leftChild(position);
			int right = rightChild(position);
			if (left != -1 && comparator(heapData[left], heapData[position]))
				optimal = left;

			if (right != -1 && comparator(heapData[right], heapData[optimal]))
				optimal = right;

			if (optimal == position)
				break;
			else
			{
				swap(heapData[optimal], heapData[position]);
				position = optimal;
			}
		}

		return top;
	}
};

void ReadNumbers(vector<int>& numbers)
{
	ifstream fHandle("C:\\Median.txt");

	string line;
	while (getline(fHandle, line))
		numbers.push_back(atoi(line.c_str()));
}

void TestMinMaxHeaps()
{
	vector<int> numbers;
	ReadNumbers(numbers);

	heap minHeap([](int left, int right) {return left <= right; });
	heap maxHeap([](int left, int right) {return left >= right; });

	for (int num : numbers)
	{
		minHeap.insert(num);
	}

	while (minHeap.pop() != -1);

	for (int num : numbers)
	{
		maxHeap.insert(num);
	}
	while (maxHeap.pop() != -1);
}

int main()
{
	vector<int> numbers;
	ReadNumbers(numbers);
	vector<int> medians;
	heap minHeap([](int left, int right) {return left <= right; });
	heap maxHeap([](int left, int right) {return left >= right; });

	int answer = 0;

	for(int index = 0; index < numbers.size(); ++index)
	{
		if (minHeap.size() == maxHeap.size())
			maxHeap.insert(numbers[index]);
		else if (maxHeap.size() < minHeap.size())
			maxHeap.insert(numbers[index]);
		else if (minHeap.size() < maxHeap.size())
			minHeap.insert(numbers[index]);

		if (minHeap.size() > 0 && maxHeap.size() > 0)
		{
			if (minHeap.top() < maxHeap.top())
			{
				int min = minHeap.pop();
				int max = maxHeap.pop();

				minHeap.insert(max);
				maxHeap.insert(min);
			}
		}
		
		medians.push_back(maxHeap.top());

		answer = answer + medians.back();
		answer = answer % 10000;
	}

	cout << "Sum Running Medians % 10000 = " << answer << endl;

	system("Pause");
	
	return 0;
}
