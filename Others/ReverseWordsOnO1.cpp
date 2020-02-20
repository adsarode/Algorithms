#include <iostream>
#include <string>
#include <ctype.h>

// Given a string as an input
// This algorithm reverses each word in the string 
// Only words are reversed order of words is not
// Time Complexity O(n), Space Complexity O(1)

int main()
{
	std::string ioString("This is odd string reversal problem");

	int stringSize = ioString.size();

	int lastSpace = -1;
	for (int currentIndex = 1; currentIndex <= stringSize; currentIndex++)
	{
		if (isspace(ioString[currentIndex]) || ioString[currentIndex] == '\0')
		{
			for (int fromChar = lastSpace + 1, toChar = currentIndex - 1; fromChar < toChar; fromChar++, toChar--)
			{
				std::swap(ioString[fromChar], ioString[toChar]);
			}

			lastSpace = currentIndex;
		}
	}

	return 0;
}