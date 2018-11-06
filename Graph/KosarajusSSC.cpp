/*
	Implementation of Kosaraju's Strongly Connected Components Algorithm
	
	https://en.wikipedia.org/wiki/Kosaraju%27s_algorithm
	
	Ashish Sarode 3 Aug 2018
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stack>
#include <map>
#include <fstream>
using namespace std;

class kosarajusSCC {

private:
	const int numVertices;
	const string fileName;

	vector<vector<int>> graphEdges;
	vector<vector<int>> graphEdgesCorr;
	vector<vector<int>> revGraphEdges;
	vector<int> revGraphOrder;
	vector<int> graphOrder;
	vector<int> leaderSCC;
	vector<int> descSCCSizes;

	int nodeOrder;
	int currentLeader;
public:

	kosarajusSCC(const int iNumVertices, const string& iFileName)
		: numVertices(iNumVertices),
		fileName(iFileName),
		revGraphOrder(numVertices + 1, -1),
		graphOrder(numVertices + 1, -1),
		leaderSCC(numVertices + 1, -1)
	{
		// Additional 1 is kept so that the 0 based index should not bother us
		// Ignoring 0th entry... indexing start from 1 to numVertices
		graphEdges.resize(numVertices + 1);
		graphEdgesCorr.resize(numVertices + 1);
		revGraphEdges.resize(numVertices + 1);
	}

	void ReadEdges()
	{
		ifstream fHandle("C:\\SCC.txt");

		const char input_delimiter = ' ';
		string line;
		int start, end;
		cout << "Reading Edges" << endl;
		while (getline(fHandle, line))
		{
			stringstream line_stream(line);
			line_stream >> start >> end;

			graphEdges[start].push_back(end);
			revGraphEdges[end].push_back(start);
		}
		cout << "Reading Edges Complete" << endl;
	}

	void DFSRev(int nodei)
	{
		stack<int> stackNodes;
		stackNodes.push(nodei);
		int node = -1;
		revGraphOrder[nodei] = 0;	// Mark visited
		while (!stackNodes.empty())
		{
			node = stackNodes.top();
			for (int tailNode : revGraphEdges[node])
			{
				if (revGraphOrder[tailNode] == -1)
				{
					revGraphOrder[tailNode] = 0;	// Mark visited
					stackNodes.push(tailNode);
					break;
				}
			}

			if (node == stackNodes.top())	// If no children are remaining to be traversed
			{
				graphOrder[node] = nodeOrder++;
				stackNodes.pop();
			}
		}
	}

	void NodeNumbersBasedOnReverseDSF()
	{
		cout << "** Finding correct order numbers" << endl;
		nodeOrder = 1;
		for (int node = numVertices; node > 0; node--)
		{
			if (-1 == revGraphOrder[node])	// Node visited for the first time
			{
				DFSRev(node);
			}
		}
	}

	void CorrectNodeNumbers()
	{
		cout << "** Correcting node numbers" << endl;
		for (int node = numVertices; node > 0; --node)
		{
			int nodeCorr = graphOrder[node];
			auto& edges = graphEdges[node];
			for (int edge : edges)
			{
				graphEdgesCorr[nodeCorr].push_back(graphOrder[edge]);
			}
		}
	}

	void DFS(int nodei)
	{
		stack<int> stackNodes;
		stackNodes.push(nodei);
		leaderSCC[nodei] = nodei;
		int node = -1;
		while (!stackNodes.empty())
		{
			node = stackNodes.top();
			for (int tailNode : graphEdgesCorr[node])
			{
				if (leaderSCC[tailNode] == -1)
				{
					leaderSCC[tailNode] = currentLeader;
					stackNodes.push(tailNode);
					break;
				}
			}

			if (node == stackNodes.top())
			{
				stackNodes.pop();
			}
		}
	}

	void FindSCCsDFS()
	{
		cout << "** Detecting SCCs" << endl;
		nodeOrder = 1;
		for (int node = numVertices; node > 0; node--)
		{
			if (-1 == leaderSCC[node])	// Node visited for the first time
			{
				currentLeader = node;
				leaderSCC[node] = currentLeader;	// Assign self as leader
				DFS(node);
			}
		}
	}

	void DescendingOrderOfSCCSizes()
	{
		cout << "** Ordering SSC sizes in desceining order" << endl;
		vector<int> sccSizes(numVertices + 1, 0);
		for (int node = 1; node <= numVertices; ++node)
		{
			sccSizes[leaderSCC[node]] = sccSizes[leaderSCC[node]] + 1;
		}

		descSCCSizes = sccSizes;
		std::sort(descSCCSizes.begin(), descSCCSizes.end(), std::greater<int>());

		cout << "Descending order of Strongly Connected Components Sizes : " << endl;
		for (int size : descSCCSizes)
		{
			cout << size << "; ";

			if (size == 0)
				break;
		}
		cout << endl;
	}

	void Run()
	{
		NodeNumbersBasedOnReverseDSF();
		CorrectNodeNumbers();
		FindSCCsDFS();
		DescendingOrderOfSCCSizes();
	}

	void PrintGraphEdges()
	{
		cout << "Graph Edges : " << endl;
		for (int i = 1; i < graphEdges.size(); ++i)
		{
			cout << i << " : ";
			for (int j : graphEdges[i])
				cout << j << ",";
			cout << ";";
		}
		cout << endl;
		
		cout << "Reverse Graph Edges : " << endl;
		for (int i = 1; i < revGraphEdges.size(); ++i)
		{
			cout << i << " : ";
			for (int j : revGraphEdges[i])
				cout << j << ",";
			cout << ";";
		}
		cout << endl;

		cout << "Corrected Graph Edges : " << endl;
		for (int i = 1; i < graphEdgesCorr.size(); ++i)
		{
			cout << i << " : ";
			for (int j : graphEdgesCorr[i])
				cout << j << ",";
			cout << ";";
		}
		cout << endl;
	}
};



int main()
{
	int numVertices;
	cout << "Enter number of vertices : ";
	cin >> numVertices;
	
	string fileName;
	/*cout << "Enter file name : ";
	cin >> fileName;*/

	kosarajusSCC kosarajuSCCObj(numVertices, fileName);
	kosarajuSCCObj.ReadEdges();
	kosarajuSCCObj.Run();
	// kosarajuSCCObj.PrintGraphEdges();

	system("Pause");

	return 0;
}
