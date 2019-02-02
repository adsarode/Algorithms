#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;

int edit_distance(const string &str1, const string &str2) {
	int M = str2.length();
	int N = str1.length();

	string A = string("-") + str1;
	string B = string("-") + str2;

	vector<vector<int>> D(M+1, vector<int>(N+1));
	for (int i = 0; i <= N; ++i)
		D[0][i] = i;
	for (int j = 0; j <= M; ++j)
		D[j][0] = j;

	int insertion = 0;
	int deletion = 0;
	int match = 0;
	int mismatch = 0;

	for (int j = 1; j <= M; ++j)
	{
		for (int i = 1; i <= N; ++i)
		{
			insertion = D[j][i - 1] + 1;
			deletion = D[j - 1][i] + 1;
			match = D[j - 1][i - 1];
			mismatch = D[j - 1][i - 1] + 1;

			if (A[i] == B[j])
				D[j][i] = std::min({insertion, deletion, match});
			else
				D[j][i] = std::min({ insertion, deletion, mismatch });
		}
	}

	return D[M][N];
}

int main() {
	string str1;
	string str2;
	std::cin >> str1 >> str2;
	std::cout << edit_distance(str1, str2) << std::endl;
	
	return 0;
}
