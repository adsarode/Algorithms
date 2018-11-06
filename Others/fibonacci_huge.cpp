#include <iostream>

long long getFibonacciPicanoM(long long m) {
	if (m <= 1)
		return 1;

	if (m == 2)
		return 3;

	long long numPrev = 0;
	long long numFibo = 1;
	long long temp = 0;

	long long m2 = m*m;
	long long count = 1;
	for (count = 1; count <= m2; ++count)
	{
		temp = numFibo;
		numFibo += numPrev;
		numFibo = numFibo % m;
		numPrev = temp;

		if ((0 == numPrev) && (1 == numFibo))
			break;
	}

	return count;
}

long long get_fibonacci(long long n, long long m) {
	if (n <= 1)
		return n;

	if (n == 0)
		return 0;
	if (n == 1)
		return 1;

	long long numPrev = 0;
	long long numFibo = 1;
	long long temp = 0;

	for (long long i = 2; i <= n; ++i)
	{
		temp = numFibo;
		numFibo += numPrev;
		numFibo = numFibo % m;
		numPrev = temp;
	}

	return numFibo;
}

long long get_fibonacci_huge_fast(long long n, long long m)
{
	long long period = getFibonacciPicanoM(m);

	long long p = n%period;

	// the solution for Fn%m and Fp%m is same
	long long numFibo = get_fibonacci(p, m);

	return numFibo;
}

int main() {
	long long n, m;
	std::cin >> n >> m;
	std::cout << get_fibonacci_huge_fast(n, m) << '\n';


	/*
	// Test
	for (int i = 1; i < 50; ++i)
	std::cout << i << "\t\t : " << getFibonacciPicanoM(i) << std::endl;
	*/
}
