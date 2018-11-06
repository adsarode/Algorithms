/*
	Implementation of Karastuba algorithm
	* Fast multiplication algorithm
	
	https://en.wikipedia.org/wiki/Karatsuba_algorithm
	
	Ashish Sarode 27 July 2018
*/

#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

void makeEqualLength(string& num1, string& num2)
{
	int digits1 = num1.length();
	int digits2 = num2.length();

	if (digits1 < digits2)
	{
		int diff = digits2 - digits1;
		for (int i = 0; i < diff; ++i)
			num1.insert(num1.begin(), '0');
	}
	else if (digits2 < digits1)
	{
		int diff = digits1 - digits2;
		for (int i = 0; i < diff; ++i)
			num2.insert(num2.begin(), '0');
	}
}

string appendNZeros(const string& ac, const int n)
{
	string res = ac;
	for (int i = 0; i < n; ++i)
		res.push_back('0');

	return res;
}

string addStringNumbers(const string& a, const string& b)
{
	string result;

	int lena = a.length();
	int lenb = b.length();
	int len = max(lena, lenb);
	int carry = 0;

	string aa = a;
	string bb = b;
	makeEqualLength(aa, bb);
	reverse(aa.begin(), aa.end());
	reverse(bb.begin(), bb.end());

	for (int i = 0; i < len; i++)
	{
		int num = 0;
		if (i < lena && i < lenb)
			num = (aa[i] - '0') + (bb[i] - '0');
		else if (i < lena)
			num = aa[i] - '0';
		else
			num = bb[i] - '0';

		num = num + carry;

		if (num >= 10)
		{
			carry = num / 10;
			char digit = (num % 10) + '0';
			result.insert(result.begin(), digit);
		}
		else
		{
			carry = 0;
			char digit = num + '0';
			result.insert(result.begin(), digit);
		}
	}
	if (carry != 0)
	{
		char digit = carry + '0';
		result.insert(result.begin(), digit);
	}

	return result;
}

/*
Assumes that
1. The numbers have equal number of digits.
2. There are only values 0-9 in strings.
*/
string karastubaAlgorithm(const string& num1, const string& num2)
{
	string result;
	if (num1.length() == 1)
	{
		int n1 = atoi(num1.c_str());
		int n2 = atoi(num2.c_str());

		int mult = n1 * n2;

		result = std::to_string(mult);
	}
	else
	{
		int n = num1.length();
		int halfLen = n / 2;

		string a(num1.begin(), num1.begin() + halfLen);
		string b(num1.begin() + halfLen, num1.end());

		string c(num2.begin(), num2.begin() + halfLen);
		string d(num2.begin() + halfLen, num2.end());

		string ac = karastubaAlgorithm(a, c);
		string bd = karastubaAlgorithm(b, d);

		// Ideally ad + bc = (a+b)*(c+d) - ac - bd 
		// But it requires implementation of subtraction operator for string numbers... 
		string ad = karastubaAlgorithm(a, d);
		string bc = karastubaAlgorithm(b, c);

		string ac_10n = appendNZeros(ac, n);

		string ad_p_bc = addStringNumbers(ad, bc);
		string ad_p_bc_10nb2 = appendNZeros(ad_p_bc, halfLen);

		result = addStringNumbers(ac_10n, ad_p_bc_10nb2);
		result = addStringNumbers(result, bd);
	}

	return result;
}

int main()
{
	/*while (true)
	{
	string num1 = "1234";
	string num2 = "5678";

	cin >> num1;
	cin >> num2;

	makeEqualLength(num1, num2);
	cout << num1 << ", " << num2 << endl;

	string multiplication = karastubaAlgorithm(num1, num2);

	cout << num1 << "*" << num2 << " = " << multiplication;
	}*/

	string num1 = "3141592653589793238462643383279502884197169399375105820974944592";
	string num2 = "2718281828459045235360287471352662497757247093699959574966967627";

	makeEqualLength(num1, num2);
	cout << num1 << ", " << num2 << endl;

	string multiplication = karastubaAlgorithm(num1, num2);

	cout << num1 << "*" << num2 << " = " << multiplication;

	system("pause");
	return 0;
}