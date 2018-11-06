/*
	Check whether binary tree or not
	
	***
	Input:
	3
	2 1 2
	1 -1 -1
	3 -1 -1
	Output:
	CORRECT
	
	***
	Input:
	3
	1 1 2
	2 -1 -1
	3 -1 -1
	Output:
	INCORRECT
	
	Ashish Sarode 18 August 2018
*/

#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>
#include <climits>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::stack;

struct Node {
	int key;
	int left;
	int right;

	Node() : key(0), left(-1), right(-1) {}
	Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

bool IsBinarySearchTree(const vector<Node>& tree) {
	// Implement correct algorithm here

	if (tree.empty())
		return true;

	stack<int> stackKeys;

	int currentKey = 0;
	int previousKey = -1;
	bool traverse = true;
	bool poppedFromStack = false;
	int nIndex = 0;
	int value = INT_MIN;

	while (traverse)
	{
		if (-1 != tree[currentKey].left && !poppedFromStack)
		{
			stackKeys.push(currentKey);
			previousKey = currentKey;
			currentKey = tree[currentKey].left;
			poppedFromStack = false;
		}
		else
		{
			if (-1 != previousKey && tree[currentKey].left == previousKey)
			{
				if (value >= tree[currentKey].key)
					return false;
			}
			else
			{
				if (value > tree[currentKey].key)
					return false;
			}

			value = tree[currentKey].key;


			if (-1 != tree[currentKey].right)
			{
				previousKey = currentKey;
				currentKey = tree[currentKey].right;
				poppedFromStack = false;
			}
			else
			{
				if (!stackKeys.empty())
				{
					previousKey = currentKey;
					currentKey = stackKeys.top();
					stackKeys.pop();
					poppedFromStack = true;
				}
				else
					traverse = false;
			}
		}
	}

	return true;
}

int main() {
	int nodes;
	cin >> nodes;
	vector<Node> tree;
	tree.reserve(nodes);
	for (int i = 0; i < nodes; ++i) {
		int key, left, right;
		cin >> key >> left >> right;
		tree.push_back(Node(key, left, right));
	}
	if (IsBinarySearchTree(tree)) {
		cout << "CORRECT" << endl;
	}
	else {
		cout << "INCORRECT" << endl;
	}
	return 0;
}
