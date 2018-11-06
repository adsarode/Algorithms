#include <iostream>

int gcd_naive(int a, int b) {
	int current_gcd = 1;
	for (int d = 2; d <= a && d <= b; d++) {
		if (a % d == 0 && b % d == 0) {
			if (d > current_gcd) {
				current_gcd = d;
			}
		}
	}
	return current_gcd;
}

int gcd_efficient(int a, int b) {
	if (0 == b)
		return a;

	if (0 == a)
		return b;

	if (1 == a || 1 == b)
		return 1;

	if (a < b)
		std::swap(a, b);

	int temp = 0;
	while (b != 0)
	{
		temp = b;
		b = a % temp;
		std::swap(temp, a);
	}

	return a;
}

int main() {
	int a, b;
	std::cin >> a >> b;
	std::cout << gcd_efficient(a, b) << std::endl;
	return 0;
}
