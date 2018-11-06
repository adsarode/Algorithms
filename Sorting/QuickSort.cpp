#include <iostream>
#include <vector>
#include <cstdlib>

using std::vector;
using std::swap;

int partition2(vector<int> &a, int l, int r) {
	int x = a[l];
	int j = l;
	for (int i = l + 1; i <= r; i++) {
		if (a[i] <= x) {
			j++;
			swap(a[i], a[j]);
		}
	}
	swap(a[l], a[j]);
	return j;
}

void randomized_quick_sort(vector<int> &a, int l, int r) {
	if (l >= r) {
		return;
	}

	int k = l + rand() % (r - l + 1);
	swap(a[l], a[k]);
	int m = partition2(a, l, r);

	randomized_quick_sort(a, l, m - 1);
	randomized_quick_sort(a, m + 1, r);
}

void partition3(vector<int> &a, int l, int r, int& m1, int&m2) {
	int x = a[l];
	m1 = l;
	m2 = l;
	int m3 = r;

	while (m2 != m3)
	{
		if (a[m2 + 1] == a[m1])
		{
			m2++;
		}
		else if (a[m2 + 1] > a[m1])
		{
			swap(a[m2+1], a[m3]);
			m3--;
		}
		else // if (a[m2 + 1] < a[m1]) No need to write this condition
		{
			swap(a[m2 + 1], a[m1]);
			m1++;
			m2++;
		}
	}
}

void randomized_quick_sort3(vector<int> &a, int l, int r) {
	if (l >= r) {
		return;
	}

	int k = l + rand() % (r - l + 1);
	// swap(a[l], a[k]);
	int m1 = l;
	int m2 = l;
	partition3(a, l, r, m1, m2);

	randomized_quick_sort3(a, l, m1 - 1);
	randomized_quick_sort3(a, m2 + 1, r);
}

int main() {
	int n;
	std::cin >> n;
	vector<int> a(n);
	for (size_t i = 0; i < a.size(); ++i) {
		std::cin >> a[i];
	}
	randomized_quick_sort3(a, 0, a.size() - 1);
	for (size_t i = 0; i < a.size(); ++i) {
		std::cout << a[i] << ' ';
	}
}
