
#include <bits/stdc++.h>

using std::cout;
using std::endl;
using std::string;

const size_t num_of_chars = 256;

string FindMinWinSubstr(string big, string small);
void InitHash(size_t hash[], size_t len, string str);

int main(void)
{
	string big1 = "ombabadugunda";
	string small1 = "nau";
	string big2 = "this is a test string";
	string small2 = "tist";
	
	cout << "min substring1: " << FindMinWinSubstr(big1, small1) << endl;
	cout << "min substring2: " << FindMinWinSubstr(big2, small2) << endl;
	
	return 0;
}


string FindMinWinSubstr(string big, string small)
{
	size_t len_big = big.length();
	size_t len_small = small.length();
	
	if (len_big < len_small)
	{
		cout << "no such window exists\n";
		
		return "";
	}
	
	size_t hash_big[num_of_chars] = {0};
	size_t hash_small[num_of_chars] = {0};
	
	InitHash(hash_small, len_small, small);
	
	size_t start = 0;
	int start_indx = -1;
	int min_len = INT_MAX;
	size_t count = 0;
	
	for (size_t i = 0; i < len_big; ++i)
	{	
		if (++hash_big[(int)big[i]] <= hash_small[(int)big[i]])
		{
			++count;
		}
		
		if (len_small == count)
		{
			while ((hash_big[(int)big[start]] > hash_small[(int)big[start]]) ||
					(0 == hash_small[(int)big[start]]))
			{
				if (hash_big[(int)big[start]] > hash_small[(int)big[start]])
				{
					--hash_big[(int)big[start]];
				}
				++start;
			}
			
			int win_len = i - start + 1;
			if (min_len > win_len)
			{
				min_len = win_len;
				start_indx = start;
			}
		}
		
	}
	
	if (-1 == start_indx)
	{
		cout << "no such window exists\n";
		
		return "";
	}
	
	return big.substr(start_indx, min_len);
}

void InitHash(size_t hash[], size_t len, string str)
{
	for (size_t i = 0; i < len; ++i)
	{
		++hash[(int)str[i]];	
	}
}


