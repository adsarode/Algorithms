/*
	Binary Tree Traversals
	In / Pre / Post
	
	https://en.wikipedia.org/wiki/Tree_traversal
	
	Non recursive implementations
	
	Input:
	5
	4 1 2
	2 3 4
	5 -1 -1
	1 -1 -1
	3 -1 -1
	Output:
	1 2 3 4 5 IN
	4 2 1 3 5 PRE
	1 3 2 5 4 POST
	
	Ashish Sarode 18 August 2018
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using std::vector;
using std::stack;
using std::ios_base;
using std::cin;
using std::cout;

class TreeOrders {
	int n;
	vector <int> key;
	vector <int> left;
	vector <int> right;

public:
	void read() {
		cin >> n;
		key.resize(n);
		left.resize(n);
		right.resize(n);
		for (int i = 0; i < n; i++) {
			cin >> key[i] >> left[i] >> right[i];
		}
	}


	vector <int> in_order() {
		vector<int> result(key.size());
		// Finish the implementation
		// You may need to add a new recursive method to do that

		stack<int> stackKeys;
		int currentKey = 0;
		bool traverse = true;
		bool poppedFromStack = false;
		int nIndex = 0;
		while (traverse)
		{
			if (-1 != left[currentKey] && !poppedFromStack)
			{
				stackKeys.push(currentKey);
				currentKey = left[currentKey];
				poppedFromStack = false;
			}
			else
			{
				result[nIndex++] = key[currentKey];
				if (-1 != right[currentKey])
				{
					currentKey = right[currentKey];
					poppedFromStack = false;
				}
				else
				{
					if (!stackKeys.empty())
					{
						currentKey = stackKeys.top();
						stackKeys.pop();
						poppedFromStack = true;
					}
					else
						traverse = false;
				}
			}
		}

		return result;
	}

	vector <int> pre_order() {
		vector<int> result(key.size());
		// Finish the implementation
		// You may need to add a new recursive method to do that

		stack<int> stackKeys;
		int currentKey = 0;
		bool traverse = true;
		int nIndex = 0;

		result[nIndex++] = key[currentKey];
		while (traverse)
		{
			if (-1 != right[currentKey])
				stackKeys.push(right[currentKey]);

			if (-1 != left[currentKey])
			{
				result[nIndex++] = key[left[currentKey]];
				currentKey = left[currentKey];
			}
			else
			{
				if (!stackKeys.empty())
				{
					currentKey = stackKeys.top();
					result[nIndex++] = key[currentKey];
					stackKeys.pop();
				}
				else
					traverse = false;
			}
		}

		return result;
	}

	vector <int> post_order() {
		vector<int> result(key.size());
		// Finish the implementation
		// You may need to add a new recursive method to do that

		stack<int> stackKeys;
		int currentKey = 0;
		int previousKey = -1;
		int nIndex = 0;
		bool hasChildren = false;

		stackKeys.push(0);
		while (!stackKeys.empty())
		{
			currentKey = stackKeys.top();

			if (-1 == previousKey || left[previousKey] == currentKey || right[previousKey] == currentKey)
			{
				if (-1 != left[currentKey])
					stackKeys.push(left[currentKey]);
				else if (-1 != right[currentKey])
					stackKeys.push(right[currentKey]);
			}
			else if (previousKey == left[currentKey])
			{
				if (-1 != right[currentKey])
					stackKeys.push(right[currentKey]);
			}
			else
			{
				result[nIndex++] = key[currentKey];
				stackKeys.pop();
			}

			previousKey = currentKey;
		}

		return result;
	}
};

void print(vector <int> a) {
	for (size_t i = 0; i < a.size(); i++) {
		if (i > 0) {
			cout << ' ';
		}
		cout << a[i];
	}
	cout << '\n';
}

int main_with_large_stack_space() {
	ios_base::sync_with_stdio(0);
	TreeOrders t;
	t.read();
	print(t.in_order());
	print(t.pre_order());
	print(t.post_order());
	return 0;
}

int main(int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
	// Allow larger stack space
	const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
	struct rlimit rl;
	int result;

	result = getrlimit(RLIMIT_STACK, &rl);
	if (result == 0)
	{
		if (rl.rlim_cur < kStackSize)
		{
			rl.rlim_cur = kStackSize;
			result = setrlimit(RLIMIT_STACK, &rl);
			if (result != 0)
			{
				std::cerr << "setrlimit returned result = " << result << std::endl;
			}
		}
	}
#endif

	return main_with_large_stack_space();
}

