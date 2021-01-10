#include <iostream>
#include <cstdio>
#include <algorithm>
#include <unordered_map>
#include <cctype>
#include <vector>
using namespace std;


bool isUniqueByMap(string s)
{
	unordered_map<char, bool> cmap;
	
	for (int i = 0; i < s.length(); ++i) {
		if (cmap.find(s[i]) != cmap.end())
		{
			return false;
		}
		cmap[s[i]] = true;
	}
	return true;
}

bool isUniqueBySort(string s)
{
	sort(s.begin(), s.end());
	for (int i = 1; i < s.size(); ++i)
	{
		if (s[i] == s[i - 1]) 
		{
			return false;
		}
	}
	return true;
}


/* isUnique - Way solution describes.
* 1. Ask interviewers assumend character set
* 2. If ASCII, set array with size 128 which indices are matched with ascii character respectively.
* 3. Iterate a given string and check a character occurs before or not.
* 4. Space Complexity: O(1), Time Complexity: O(1) because it iterates at most 128.
* 5. If we not use additional space,
*		if string manipulation is permitted, sort string then check.
*			be careful about sort algorithm does not use additional space.
*			Time Complexity: O(n * log n)
*		else check characters in each positions and Time Complexity is O(n^2)
*/


bool checkPermutation(string s1, string s2)
{
	if (s1.size() != s2.size())
	{
		return false;
	}

	unordered_map<char, int> cmap;
	for (int i = 0; i < s1.length(); ++i)
	{
		if (cmap.find(s1[i]) == cmap.end())
		{
			cmap[s1[i]] = 0;
		}
		++cmap[s1[i]];
	}
	for (int i = 0; i < s2.length(); ++i)
	{
		if (cmap.find(s2[i]) == cmap.end())
		{
			return false;
		}
		--cmap[s2[i]];
	}

	unordered_map<char, int>::iterator it = cmap.begin();
	while (it != cmap.end())
	{
		if (it->second != 0)
		{
			return false;
		}
		++it;
	}
	return true;
}

/* checkPermutation - Way solution describes.
* 1. clarify it is case sensitive or not.
* 2. clarify it is space sensitive or not.
* 3. clarify a given character set.
* 4. Firstly, if two arrays has different length, return false.
* 5. Then first solution is sorting two arrays, then compare each characters.
* 6. Second solution is define array of character count (length 128 for ascii), then count occurence of first string
*		and reduct for second string, if some value is negative while iterating, return false, else return true
*		this is because if they are not permutation, there should be at least one negative count character.
*/


string urlify(string s)
{
	string us;
	bool continued = false;

	for (int i = 0; i < s.length(); ++i)
	{
		char c = s[i];
		if (c != ' ')
		{
			us.push_back(c);
			continued = false;
		}
		else if (!continued)
		{
			us.append("%20");
			continued = true;
		}
	}
	if (us.length() > 2 && us.substr(us.length()-3, 3) == "%20")
	{
		us = us.substr(0, us.length() - 3);
	}
	if (us.length() > 2 && us.substr(0, 3) == "%20")
	{
		us = us.substr(3, us.length());
	}

	return us;
}


/* urlify - Way solution describes.
* 1. Assuming start with non-space character.
* 2. Assuming spaces between characters cannot be continued.
* 3. Find true length of string, the end of last non-space character.
* 4. Count spaces.
* 5. Set index = true length + 2*spaces
* 6. For loop reversely,
* 		- If character is space, then set "%20" at index - 1 ~ index - 3, then index -= 3
		- Else set a given character at index-1, then index -= 1
*/



// Assume s is composed of only spaces and english alphabets.
bool palindromePermutation(string s)
{
	unordered_map<char, int> cmap;

	for (int i = 0; i < s.length(); ++i)
	{
		char c = s[i];
		if (c == ' ')
		{
			continue;
		}

		c = tolower(c);
		if (cmap.find(c) == cmap.end())
		{
			cmap[c] = 0;
		}
		++cmap[c];
	}

	int numOdd = 0;
	unordered_map<char, int>::iterator it = cmap.begin();
	while (it != cmap.end())
	{
		if (it->second % 2) 
		{
			++numOdd;
		}
		if (numOdd > 1)
		{
			return false;
		}
		++it;
	}
	return true;
}


/* palindromePermutation - Way solution describes.
* 3 Ways are described.
* Way1 is same for my way except using fixed size int array.
* Way2 is similar but it calculates the number of odds while updating int array. 
*	Thus the number of odds might fluctuate.
* Way3 uses bit vector. Counts is not important. Odd or even is important.
	Bit vector can be utilized to record count is odd or even.
	Then we know that if palindrome, all bits are 0 or only one bit is 1.
	Let x be a bit vector. Assume it is big endian. 
	Then we can expect that (x-1) & x == 0 if palindrome.
		This is because if all bits are 0, this is obvious.
		If only one bit is 1, x-1 makes this bit to 0 and changing following bit to 1. So & operation results in 0.
		If more than two bits are 1, x-1 toggle only following bits after small bit. (e,g. 1000100 >> 1000011)
		So & operation keeps leading 1 bit and the result cannot be 0.
*/


// Assume all characters are lowercase english and not empty.
bool oneAway(string s1, string s2)
{
	int sz1 = s1.length(), sz2 = s2.length();
	if (abs(sz1 - sz2) > 1) {
		return false;
	}
	if (sz1 == sz2)
	{
		int numSkip = 0;
		for (int i = 0; i < sz1; ++i)
		{
			if (s1[i] != s2[i])
			{
				if (++numSkip > 1)
				{
					return false;
				}
			}
		}
		return true;
	}

	string sLong, sShort;
	int szLong, szShort;
	if (sz1 > sz2)
	{
		sLong = s1;
		sShort = s2;
		szLong = sz1;
		szShort = sz2;
	}
	else
	{
		sLong = s2;
		sShort = s1;
		szLong = sz2;
		szShort = sz1;
	}

	int iLong = 0, iShort = 0, numSkip = 0;
	while (iLong < szLong)
	{
		if (iShort == szShort)
		{
			return true;
		}
		else if (sLong[iLong] == sShort[iShort])
		{
			++iLong;
			++iShort;
		}
		else
		{
			++iLong;
			if (++numSkip > 1)
			{
				return false;
			}
		}
	}
	return true;
}


/* oneAway - Way solution describes.
* The way suggested is same with that I implemented.
* However way in the book goes further in one step 
* with suggesting merging replacement loop and removal loop.
* In a merged loop, check length of strings and do something. (removal or replacement)
*/


string stringCompression(string s)
{
	string cs;
	int lenS = s.length();
	
	char c = s[0];
	int n = 0, i = 0;
	while (i <= lenS)
	{
		if (i == lenS || s[i] != c)
		{
			cs.push_back(c);
			cs.append(to_string(n));
			if (cs.length() >= lenS)
			{
				return s;
			}
			if (i == lenS)
			{
				return cs;
			}
			else
			{
				c = s[i];
				n = 1;
			}
		}
		else
		{
			++n;
		}
		++i;
	}
	return cs;
}


/* stringCompression - Way solution describes.
* The way suggested is same with that I implemented.
* The difference is that my implementation integrated 
*	making compressed string and comparing length of two strings in a loop,
*	while codes suggested is splitting this method.
*	One cannot be more efficient than the other.
*/


void printMatrix(vector<vector<char>> m, int n)
{
	printf("\n");
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			printf("%d ", m[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}


void printMatrix(vector<vector<int>> m)
{
	printf("\n");
	for (int i = 0; i < m.size(); ++i)
	{
		for (int j = 0; j < m[0].size(); ++j)
		{
			printf("%d ", m[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}


vector<vector<char>> rotateMatrix(vector<vector<char>> &m)
{
	int n = m.size();
	int d = (n + 1) / 2;

	for(int l = 0; l < d; ++l)
	{
		for (int i = 0; i < n - 1 - 2*l; ++i)
		{
			char a = m[l][l+i];
			char b = m[l+i][n-1-l];
			char c = m[n-1-l][n-1-l-i];
			char d = m[n-1-l-i][l];

			m[n-1-l-i][l] = a;
			m[n-1-l][n-1-l-i] = d;
			m[l+i][n-1-l] = c;
			m[l][l+i] = b;
		}
	}
	return m;
}


/* rotateMatrix - Way solution describes.
* The way suggested is same with that I implemented.
*/


vector<vector<int>> zeroMatrix(vector<vector<int>> &matrix)
{
	int m = matrix.size(), n = matrix[0].size();
	vector<pair<int,int>> ps;

	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (matrix[i][j] == 0)
			{
				ps.push_back(pair<int,int>(i, j));
			}
		}
	}
	for (auto p : ps)
	{
		int r = p.first, c = p.second;
		for (int j = 0; j < n; ++j)
		{
			matrix[r][j] = 0;
		}
		for (int i = 0; i < m; ++ i)
		{
			matrix[i][c] = 0;
		}
	}
	return matrix;
}


/* zeroMatrix - Way solution describes.
* The way suggested keeps row indices of zeros and column indices of zeros, respectively.
* This is more space efficient than saving pair of row index and column index of zero 
* when there are many zeros so that there are duplicated row index or column index.
*/


bool isSubstring(string s1, string s2)
{
	int sz1 = s1.length(), sz2 = s2.length();
	for (int i = 0; i < sz1 - sz2 + 1; ++i)
	{
		if (s1.substr(i, sz2) == s2)
		{
			return true;
		}
	}
	return false;
}


bool stringRotation(string s1, string s2)
{
	string ss = s1 + s1;
	return isSubstring(ss, s2);
}


/* stringRotation - Way solution describes.
* The way suggested is same with my implementation.
*/


int main()
{
	cout << "Check Permutation1: " << checkPermutation("abcwerw", "ewwrcab") << endl;
	cout << "Check Permutation2: " << checkPermutation("abcwerwb", "ewwrcabw") << endl;
	cout << "Urlify1: " << urlify(" Mr John   Smith      ") << endl;
	cout << "Urlify2: " << urlify("  ") << endl;
	cout << "palindromePermutation1: " << palindromePermutation("Tact Coa") << endl;
	cout << "palindromePermutation2: " << palindromePermutation("Tact Coaa") << endl;
	cout << "palindromePermutation3: " << palindromePermutation("Tact oCoa") << endl;
	cout << "oneAway1: " << oneAway("pale", "ple") << endl;
	cout << "oneAway2: " << oneAway("pales", "pale") << endl;
	cout << "oneAway3: " << oneAway("pale", "bale") << endl;
	cout << "oneAway4: " << oneAway("pale", "bake") << endl;
	cout << "oneAway5: " << oneAway("pales", "pal") << endl;
	cout << "stringCompression1: " << stringCompression("aabcccccaaa") << endl;
	cout << "stringCompression2: " << stringCompression("aabcca") << endl;
	
	vector<vector<char>> m1 = { 
		{ 1, 2, 3, 4, 5 }, 
		{ 6, 7, 8, 9, 10}, 
		{ 11, 12, 13, 14, 15}, 
		{ 16, 17, 18, 19, 20}, 
		{ 21, 22, 23, 24, 25},
	};
	printMatrix(m1, 5);
	printMatrix(rotateMatrix(m1), 5);

	vector<vector<char>> m2 = { 
		{ 1, 2, 3, 4, 5, -1}, 
		{ 6, 7, 8, 9, 10, -2}, 
		{ 11, 12, 13, 14, 15, -3}, 
		{ 16, 17, 18, 19, 20, -4}, 
		{ 21, 22, 23, 24, 25, -5},
		{ -6, -7, -8, -9, -10, 0},
	};
	printMatrix(m2, 6);
	printMatrix(rotateMatrix(m2), 6);

	vector<vector<int>> m3 = { 
		{ 1, 2, 3, 4, 5, -1}, 
		{ 6, 7, 8, 9, 10, -2}, 
		{ 11, 12, 0, 14, 0, -3}, 
		{ 0, 17, 18, 19, 20, -4}, 
		{ 21, 22, 23, 24, 25, -5},
		{ -6, -7, -8, -9, -10, 0},
	};
	m3 = zeroMatrix(m3);
	printMatrix(m3);
	cout << stringRotation("watterbottle", "erbottlewat") << endl;

	return 0;
}
