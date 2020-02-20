#include <iostream>

using namespace std;

// Given two sides of rectangle, thsi algorithm finds mimimum number of squares that might be created out of this rectangle
// Algorithm print number of squares of particular size followed by size

int main()
{
	int side1, side2;
	cout << "Side1 = ";
	cin >> side1;
	cout << "Side2 = ";
	cin >> side2;

	if (side1 > side2)
		std::swap(side1, side2);

	while (side1 != 0 && side2 != 0)
	{
		int numSquares = side2 / side1;
		cout << numSquares << " Squares of size = " << side1 << "x" << side1 << endl;

		int temp = side2 % side1;
		side2 = side1;
		side1 = temp;
	}

	return 0;
}

