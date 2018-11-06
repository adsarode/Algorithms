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

using namespace std;

struct tree
{
public:
	tree(long long val) : 
		value(val),
		left(nullptr),
		right(nullptr),
		parent(nullptr){};
	tree(long long val, tree* l, tree* r) :
		value(val),
		left(l),
		right(r),
		parent(nullptr) {};

	tree* left = nullptr;
	tree* right = nullptr;
	tree* parent = nullptr;
	long long value = 0;

	~tree()
	{
		left = nullptr;
		right = nullptr;
	}
};

void ReadSymbolWeights(vector<int>& weights)
{
	string line;
	ifstream fHandle("C:\\D1\\MOOCs\\Coursera\\AlgorithmsStanford\\03GreedyMSTDynPro\\huffman.txt");

	getline(fHandle, line);
	stringstream strLine(line);
	int totalWeights = -1;
	strLine >> totalWeights;

	weights.resize(totalWeights, 0);
	for (int weightIndex = 0; weightIndex < totalWeights; ++weightIndex)
	{
		getline(fHandle, line);
		weights[weightIndex] = stoi(line);
	}
}

class CompareTree
{
public:
	bool operator() (tree* t1, tree* t2)
	{
		return t1->value > t2->value;
	}
};

void postOrder(tree* node, string str, vector<pair<int, string>>& huffmanCodes)
{
	if (node->left == nullptr && node->right == nullptr)
		huffmanCodes.push_back(make_pair(node->value, str));

	if (node->left)
		postOrder(node->left, str + '0', huffmanCodes);

	if (node->right)
		postOrder(node->right, str + '1', huffmanCodes);
}

void deleteTree(tree* node)
{
	if(node->left != nullptr)
		deleteTree(node->left);

	if(node->right != nullptr)
		deleteTree(node->right);

	delete node;
}

void GenerateHuffmanCodes(vector<int>& weights, vector<pair<int, string>>& huffmanCodes)
{
	priority_queue < tree*, vector<tree*>, CompareTree> wtQueue;
	for (int wt = 0; wt < weights.size(); ++wt)
	{
		wtQueue.push(new tree(weights[wt]));
	}

	tree* root = nullptr;
	while (!wtQueue.empty())
	{
		if (wtQueue.size() == 1)
			break;

		tree* wt1 = wtQueue.top();
		wtQueue.pop();

		tree* wt2 = wtQueue.top();
		wtQueue.pop();

		root = new tree(wt1->value + wt2->value, wt1, wt2);
		wtQueue.push(root);
	}

	long long val = root->value;
	postOrder(root, "", huffmanCodes);

	deleteTree(root);
}

int main()
{
	vector<int> weights;
	ReadSymbolWeights(weights);

	vector<pair<int, string>> huffmanCodes;
	GenerateHuffmanCodes(weights, huffmanCodes);

	unsigned minLength = 9999999;
	unsigned maxLength = 0;

	ofstream fHandle("C:\\D1\\MOOCs\\Coursera\\AlgorithmsStanford\\03GreedyMSTDynPro\\huffmanCodes.txt");
	for(auto code : huffmanCodes)
	{
		unsigned len = code.second.length();
		if (len < minLength)
			minLength = len;
		else if (len > maxLength)
			maxLength = len;

		// fHandle << code.first << ": " << code.second << endl;
	} 

	cout << "For given weights, max huffman codes length = " << maxLength << " min huffman codes length = " << minLength << endl;

	system("Pause");

	return 0;
}
