/*
	Dot product of two vectors
	
	
	Ashish Sarode 20 Sept 2017
*/

#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

long long max_dot_product(vector<int> a, vector<int> b) {
	long long result = 0;

	int nSize = a.size() <= b.size() ? a.size() : b.size();

	for (size_t i = 0; i < nSize; i++) {
		
		int maxAIndex = 0;
		for (int ia = 1; ia < a.size(); ia++)
		{
			if (a[maxAIndex] < a[ia])
				maxAIndex = ia;
		}

		int maxBIndex = 0;
		for (int ib = 1; ib < b.size(); ib++)
		{
			if (b[maxBIndex] < b[ib])
				maxBIndex = ib;
		}
		long long maxA = a[maxAIndex];
		long long maxB = b[maxBIndex];
		result = result + maxA*maxB;

		a.erase(a.begin() + maxAIndex);
		b.erase(b.begin() + maxBIndex);
	}
	return result;
}

int main() {
	size_t n;
	std::cin >> n;
	vector<int> a(n), b(n);
	for (size_t i = 0; i < n; i++) {
		std::cin >> a[i];
	}
	for (size_t i = 0; i < n; i++) {
		std::cin >> b[i];
	}
	std::cout << max_dot_product(a, b) << std::endl;
}
