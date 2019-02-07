#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;
typedef unsigned long long ull;

const ull multiplier = 11;
// const ull prime = 1000003;
const ull prime = 1000000007;

struct Data {
	string pattern, text;
};

struct SearchPattern {
public:
	SearchPattern(const string& pat, const string& tex)
		: pattern(pat), text(tex), hashValues((tex.length() - pattern.length() + 1)), patLen(pattern.length()), texLen(text.length())
	{}

	void PrintNumOccurances()
	{
		PreComputeHashes();

		int range = texLen - patLen;
		for (int i = 0; i <= range; i++)
		{
			if (patternHash == hashValues[i])
			{
				bool areEqual = true;

				for (int j = 0; j < patLen; j++)
				{
					if (text[i + j] != pattern[j])
					{
						areEqual = false;
						break;
					}
				}

				if (areEqual)
					std::cout << i << " ";
			}
		}
		std::cout << std::endl;
	}

private:
	ull PolyHash(const string& s)
	{
		ull hash = 0;
		for (int i = s.size() - 1; i >= 0; --i)
			hash = (hash * multiplier + s[i]) % prime;
		return hash;
	}

	void PreComputeHashes()
	{
		// Pre compute pattern hash
		patternHash = PolyHash(pattern);

		string s(&text[texLen - patLen], &text[texLen]);
		hashValues[texLen - patLen] = PolyHash(s);

		ull y = 1;
		for (int k = 1; k <= patLen; ++k)
			y = (y * multiplier) % prime;

		for (int i = (texLen - (patLen + 1)); i >= 0; i--)
		{
//			hashValues[i] = (((multiplier*(hashValues[i + 1]) + (ull)(text[i]) - (y*((ull)(text[i + patLen]))) % prime)) + prime) % prime;
			hashValues[i] = ((multiplier*(hashValues[i + 1]) + (ull)(text[i]) - (y*((ull)(text[i + patLen]))) % prime) + prime) % prime;
		}
	}

private:
	const string &pattern;
	const string &text;

	int patLen;
	int texLen;
	ull patternHash;
	vector<ull> hashValues;
};

Data read_input() {
	Data data;
	std::cin >> data.pattern >> data.text;
	return data;
}

void get_occurrences(const Data& input) {
	SearchPattern searchPattern(input.pattern, input.text);
	searchPattern.PrintNumOccurances();
}


int main() {
	std::ios_base::sync_with_stdio(false);
	get_occurrences(read_input());
	return 0;
}
