/*
	Find closest pair of points in 2D
	
	Ashish Sarode 20 Sept 2017
*/

#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
#include <math.h>
#include <cfloat>
#include <limits>

using std::vector;
using std::string;
using std::pair;
using std::min;

const double maxDist = DBL_MAX;
const double tolerance = 0.0000001;

class Point
{
public:
	Point()
		:X(0), Y(0)
	{};

	Point(int x, int y)
		:X(x), Y(y)
	{

	}

public:
	int X;
	int Y;
};

class MinimumDistanceCalculator
{
public:
	MinimumDistanceCalculator(vector<int> &x, vector<int> &y)
	{
		std::transform(x.begin(), x.end(), y.begin(), std::back_inserter(mXY_X), [](int& xx, int& yy) {return Point(xx, yy); });

		// Sort the points based on X and Y co-ordinates
		std::sort(mXY_X.begin(), mXY_X.end(), [](const Point &left, const Point &right) { return (left.X > right.X); });
		mMinDist = maxDist;
	}
	~MinimumDistanceCalculator(){};

	void CheckForDistance(const Point& p1, const Point& p2)
	{
		double deltaY = std::abs(p1.Y - p2.Y);
		if (deltaY >= mMinDist)
			return;

		double deltaX = std::abs(p1.X - p2.X);
		if (deltaX >= mMinDist)
			return;

		double dist = sqrt(deltaX*deltaX + deltaY*deltaY);
		if (dist < mMinDist)
			mMinDist = dist;
	}

	void BruteForce(const int startIndex, const int endIndex)
	{
		for (int index1 = startIndex; index1 <= endIndex; ++index1)
		{
			for (int index2 = index1 + 1; index2 <= endIndex; ++index2)
			{
				CheckForDistance(mXY_X[index1], mXY_X[index2]);
			}
		}
	}

	void ClosestInStrip(const vector<Point>& strip)
	{
		int stripSize = strip.size();
		for (int index1 = 0; index1 < stripSize; ++index1)
		{
			for (int index2 = index1 + 1; (index2 < stripSize) && (std::abs(strip[index1].Y - strip[index2].Y) < mMinDist); ++index2)
			{
				CheckForDistance(strip[index1], strip[index2]);
			}
		}
	}

	void ClosestRecursive(const int startIndex, const int endIndex)
	{
		if (mMinDist < tolerance)	// If the minimum distance found is 0 then no need to do further computations.
			return;

		if (endIndex - startIndex <= 3)
		{
			BruteForce(startIndex, endIndex);
			return;
		}

		int midIndex = (startIndex + endIndex) / 2;
		Point midPt = mXY_X[midIndex];

		// No need to split the points with same x coordinate, these points will be covered in strip.
		int midLeft = midIndex;
		for (midLeft = midIndex; midLeft > startIndex; midLeft--)
		{
			if (mXY_X[midLeft].X != mXY_X[midIndex].X)
				break;
		}
		midLeft += 1;

		int midRight = midIndex;
		for (midRight = midIndex; midRight < endIndex; midRight++)
		{
			if (mXY_X[midRight].X != mXY_X[midIndex].X)
				break;
		}
		midRight -= 1;

		ClosestRecursive(startIndex, midLeft);
		ClosestRecursive(midRight, endIndex);

		// Create strip around mid point with mMinDist-X on either side
		int stripLeft = midLeft;
		int stripXMin = mXY_X[midIndex].X - (int)mMinDist;
		int stripXMax = mXY_X[midIndex].X + (int)mMinDist;
		for (; stripLeft > startIndex; stripLeft--)
		{
			if (mXY_X[stripLeft].X > stripXMax)
				break;
		}
		stripLeft += 1;

		int stripRight = midRight;
		for (; stripRight < endIndex; stripRight++)
		{
			if (mXY_X[stripRight].X < stripXMin)
				break;
		}
		stripRight -= 1;

		int stripSize = stripRight - stripLeft + 1;
		vector<Point> stripDelta(stripSize);
		std::copy(mXY_X.begin() + stripLeft, mXY_X.begin() + stripRight + 1, stripDelta.begin());
		std::sort(stripDelta.begin(), stripDelta.end(), [](const Point &left, const Point &right) { return (left.Y > right.Y); });
		ClosestInStrip(stripDelta);
	}

	double ClosestPointsDistance()
	{
		// Check whether X or Y spread is greater (actually variance should be checked, but variance calculation is costly.
		ClosestRecursive(0, mXY_X.size() - 1);

		return mMinDist;
	}

private:
	vector<Point> mXY_X;
	double mMinDist;
};

double minimal_distance(vector<int> &x, vector<int> &y) {
	//write your code here

	MinimumDistanceCalculator minDistCalc(x, y);
	return minDistCalc.ClosestPointsDistance();
}

int main() {
	size_t n;
	std::cin >> n;
	vector<int> x(n);
	vector<int> y(n);
	for (size_t i = 0; i < n; i++) {
		std::cin >> x[i] >> y[i];
	}
	std::cout << std::fixed;
	std::cout << std::setprecision(9) << minimal_distance(x, y) << "\n";
}
