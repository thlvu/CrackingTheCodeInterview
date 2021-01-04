#include <iostream>
#include <cstdio>
#include <algorithm>
#include <unordered_map>
using namespace std;


bool isUniqueByMap(string s)
{
	unordered_map<char, bool> cmap;

	for (auto c : s) {
		if (cmap.find(c) != cmap.end())
		{
			return false;
		}
		cmap[c] = true;
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
	for (auto c : s1)
	{
		if (cmap.find(c) == cmap.end())
		{
			cmap[c] = 0;
		}
		++cmap[c];
	}
	for (auto c : s2)
	{
		if (cmap.find(c) == cmap.end())
		{
			return false;
		}
		--cmap[c];
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



int main()
{
	cout << checkPermutation("abcwerw", "ewwrcab") << endl;
	cout << checkPermutation("abcwerwb", "ewwrcabw") << endl;
}
