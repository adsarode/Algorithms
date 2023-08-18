/*
A building has 100 floors.

An egg can be dropped from any floor.

One of the floors is the highest floor an egg can be dropped from without breaking. If an egg is dropped from above that floor, it will break.

If it is dropped from that floor or below, it will be completely undamaged and you can drop the egg again.

Given two eggs, find the highest floor an egg can be dropped from without breaking, with as few drops as possible.

Two solutions =>
1. Try floors 10,20.. 100 first and then required intervals
2. Try floors 14,27.. 100 first and then required intervals (interval 13,12,11..)

This code finds average number of attempts 

*/

#include <iostream>
#include <vector>
#include <algorithm>

int CalculateNumberOfTrials(const std::vector<int>& sortedJumpFloorNums, int targetFloor)
{
	int numTries = -1;
	int lowerIndex = -1;
	int upperIndex = -1;
	for (int index = 0; index < sortedJumpFloorNums.size(); index++)
	{
		int upperBound = sortedJumpFloorNums.at(index);
		if (targetFloor <= upperBound)		// Cannot be lower bound as it was upper bound in previous iteration and 0 in first
		{
			upperIndex = index;
			lowerIndex = index > 0 ? index - 1 : -1;

			break;
		}
	}

	if (upperIndex >= 0 && targetFloor > 0)
	{
		if (sortedJumpFloorNums.at(upperIndex) == targetFloor)
			numTries = upperIndex + 1;			// Upper Index + 1.. => index starts with 0
		else
		{
			int lowerBound = lowerIndex >= 0 ? sortedJumpFloorNums.at(lowerIndex) : 0;
			int individualTries = targetFloor - lowerBound;
			numTries = upperIndex + 1 + individualTries;
		}
	}

	if (numTries < 0)
		cout << "Target Floor out of range" << endl;

	return numTries;
}

void CalculateAverageNumAttempts10Interval()
{
	std::vector<int> jumpIntervals = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };

	int totalNumAttempts = 0;
	for (int numFloor = 1; numFloor <= 100; numFloor++)
	{
		int numAttempts = CalculateNumberOfTrials(jumpIntervals, numFloor);
		cout << "Floor Number = " << numFloor << "; Required Attempts = " << numAttempts << endl;
		if(numAttempts > 0)
			totalNumAttempts += numAttempts;
	}

	double averageNumAttempts = totalNumAttempts / 100.0;

	cout << "** Average Number of Attempts with Interval of 10 = " << averageNumAttempts << endl;
}

void CalculateAverageNumAttemptsDynamicInterval()
{
	/*
	* Create Jump Intervals
	*/
	std::vector<int> jumpIntervals;
	int jumpTrialFloor = 0;
	for (int jumpInterval = 14; jumpInterval > 0; jumpInterval--)
	{
		jumpTrialFloor += jumpInterval;
		if (jumpTrialFloor > 100)
			jumpTrialFloor = 100;

		jumpIntervals.push_back(jumpTrialFloor);

		if (jumpTrialFloor == 100)
			break;
	}

	int totalNumAttempts = 0;
	for (int numFloor = 1; numFloor <= 100; numFloor++)
	{
		int numAttempts = CalculateNumberOfTrials(jumpIntervals, numFloor);
		cout << "Floor Number = " << numFloor << "; Required Attempts = " << numAttempts << endl;
		if (numAttempts > 0)
			totalNumAttempts += numAttempts;
	}

	double averageNumAttempts = totalNumAttempts / 100.0;

	cout << "** Average Number of Attempts with Dynamic Interval = " << averageNumAttempts << endl;
}

int main()
{
	CalculateAverageNumAttempts10Interval();

	cout << endl << endl;

	CalculateAverageNumAttemptsDynamicInterval();

	return 0;
}
