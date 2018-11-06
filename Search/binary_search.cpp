#include <iostream>
#include <cassert>
#include <vector>

using std::vector;

int binary_search(const vector<int> &a, int x) {
	int left = 0, right = (int)(a.size() - 1);
	//write your code here

	if (a[left] == x)
		return left;
	else if (a[right] == x)
		return right;

	int middle = 0;

	while ((right - left) > 1)
	{
		middle = (left + right) / 2;

		if (a[middle] == x)
			return middle;

		if ((x < a[left]) || (x > a[right]))
			return -1;

		if (x < a[middle])
			right = middle;
		else
			left = middle;
	}

	return -1;
}

int linear_search(const vector<int> &a, int x) {
	for (size_t i = 0; i < a.size(); ++i) {
		if (a[i] == x) return i;
	}
	return -1;
}

int main() {
	int n;
	std::cin >> n;
	vector<int> a(n);
	for (size_t i = 0; i < a.size(); i++) {
		std::cin >> a[i];
	}
	int m;
	std::cin >> m;
	vector<int> b(m);
	for (int i = 0; i < m; ++i) {
		std::cin >> b[i];
	}
	for (int i = 0; i < m; ++i) {
		//replace with the call to binary_search when implemented
		std::cout << binary_search(a, b[i]) << ' ';
	}
}
