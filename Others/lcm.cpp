#include <iostream>

long long lcm_naive(int a, int b) {
	for (long l = 1; l <= (long long)a * b; ++l)
		if (l % a == 0 && l % b == 0)
			return l;

	return (long long)a * b;
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

long long lcm_efficient(int a, int b) {
	
	if (0 == a || 0 == b)
		return 0;

	long long gcd = gcd_efficient(a, b);
	long long lla = a;
	long long llb = b;
	
	return (lla*(llb / gcd));
}

int main() {
	int a, b;
	std::cin >> a >> b;
	std::cout << lcm_efficient(a, b) << std::endl;
	return 0;
}
