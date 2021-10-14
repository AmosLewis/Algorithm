//laioffer14_DP2.cpp


// Q0 Minimum Numbers of Jumps
int jumpgame(vector<int>& A)
{
	vector<int> M(A.size(), -1);	//当前元素最小跳几步可以跳到最后
	for(int i = A.size() - 1; i >= 0; i++) // 从最后一个元素开始遍历
	{
		int min_step = 0;
		for(int j = 0; j < min(n, A[i]); i++)// 找到A[i]后面的A[i]个元素中最小的那个
		{
			min_step = min(min_step, M[i + j]);
		}
		M[i] = min_step + 1; 
	}
	return M[0];
}

// Q1 largest sum of subarray
// A [1 2 4 -1 -20 10 -1]
// M [1 3 7 6  -14 10 9] 

int largestSumOfSubarray(vector<int>& A)
{
	int global_max = INT_MIN;
	vector<int> M(A.size(), 0);
	M[0] = A[0];
	for(int i = 1; i < A.size(); i++)
	{
		int cursum = M[i-1] + A[i];
		if(cursum >= 0)
		{
			M[i] = cursum;
		}else
		{
			M[i] = A[i];
		}
		if(global_max < M[i])
		{
			global_max = M[i];
		}
	}
	return global_max;
}
// follow up 1: space complexity O(1)
int largestSumOfSubarray(vector<int>& A)
{
	int global_max = INT_MIN;
	int M = A[0];
	for(int i = 1; i < A.size(); i++)
	{
		if(cursum >= 0)
		{
			M = M + A[i];
		}else
		{
			M = A[i];
		}
		global_max = max(global_max, M);
	}
	return global_max;
}

// follow up2: return start and end for global_max result;
vector<int> largestSumOfSubarray(vector<int>& A)
{
	int global_max = INT_MIN;
	vector<int> M(A.size(), 0);
	M[0] = A[0];
	int temp_start = 0;
	int temp_end = 0;
	int global_start = 0;
	int global_end = 0;
	for(int i = 1; i < A.size(); i++)
	{
		end = i;
		int cursum = M[i-1] + A[i];
		if(cursum >= 0)
		{
			M[i] = cursum;
		}else
		{
			M[i] = A[i];
			start = i;
		}
		if(global_max < M[i])
		{
			global_max = M[i];
			global_start = start;
			global_end = end;
		}
	}
	return {global_max, global_start, global_end}};
}



// Q2 Dictionary word problem
// word 是否可以由dic中的string组成？
// 0 1 2 3 4 5 6
// a b c d e f g
//	 j   i
bool DictionaryWord(vector<string>& dic, string& word)
{
	unordered_set<string> hash_set;
	for(const auto& it : dic)
	{
		hash_set.push(it);
	}

	// 从0-i的元素是否可以由dic中的元素组成，
	// 即长度为i+1的word是否可以由dic中的元素组成
	vector<bool> M(word.size() + 1, false);
	//M[0] = fasle; // 空char“” 作为左边，不在字典里
	for(int i = 1; i < word.size(); i++) // 单词长度i一点一点地grow上去，
	{
		// case 0， 整个单词都在字典里 , 一刀都不切，整个单词都是右小段
		// if the word in the dictionary
		if(hash_set.count(word))
		{
			M[i] = true;
			continue;
		}
		// check possible single split
		// 对单词切成左大段，右小段
		// 左大段的长度由1 到i-1
		for(int j = 1; j < i; j++)
		{
			// check subproblem:长度为j的左大段在上一轮循环中已经解决过，存在M[j]中
			// check the rest of the word
			if(M[j] && dic.count(word.substr(j, i-j)))
			{
				M[i] = true;
				break;
			}
		}
	}
	return M[word.size()];
}
// Time: O(n^3)
// 注意 substr的时间复杂度是O(n)的



// Edit distance
// solution 1
int editDistance(string& str1, string$ str2)
{
	// base case
	if(str1.empty())
	{
		return str2.size();
	}
	if(str2.empty())
	{
		return str1.size();
	}

	// 1. check what the distance is if the characters[0] are identical
	int Nothing = INT_MAX;
	if(str1[0] == str2[0])
	{
		Nothing = editDistance(str1.substr(1), str2.substr(1));
	}

	// 2. replace/Delete/Insert first element in str1
	int Replace = 1 + editDistance(str1.substr(1), str2.substr(1));
	int Delete = 1 + editDistance(str1.substr(1), str2);
	int Insert = 1 + editDistance(str1, str2.substr(1));

	return min(Nothing, Replace, Delete, Insert);
}
// Time: O(4^2n)
// 这个代码有几个坏处， substr, 可以改成index
// 时间复杂度太差，onsite肯定不过

int editDistance(string& str1, string& str2)
{
	int m = str1.size() + 1; 
	int n = str2.size() + 1;
	vector<vector<int>> M(m, vector<int>(n, 0)); // 这个可以优化，因为DP时候只用了两行的信息，但是我不知道怎么优化
	// str1 是空，要变成str2, 就是str2有几个字符就变几次
	for(int i = 0; i < n; i++)
	{
		M[0][i] = i;
	}
	// str2是空
	for(int i = 1; i < n; i++)
	{
		M[i][0] = i;
	}

	for(int i = 1; i < m; i++)
	{
		for(int j = 1; j < n; j++)
		{
			M[i][j] = (str1[i] == str[j]) ? M[i-1][j-1] :
						 (1 +
						 	min(
						 		M[i-1,j-1], 
						 		min(M[i-1][j], M[i][j-1]
						 		)
						    )
						 );
		}
	}
}


// Q4 Largest square of 1's in a binary matrix
int largeSquare(vector<vector<int>>& A)
{
	int n = A.size();
	vector<vector<int>> M(n, vector<int>(n, 0));
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			if(A[i][j] == 0)
			{
				M[i][j] = 0
			}else
			{
				M[i][j] = 1 + 
							min(
						 		M[i-1,j-1], 
						 		min(M[i-1][j], M[i][j-1]
						 		)
						    );
			}
		}
	}
}



// 练习
int largestSumOfSubarray(vector<int>& A)
{
	int n = A.size();
	if(A.size() == 0)
	{
		return -1;
	}
	vector<int> M(n, 0);
	// base case
	M[0] = A[0];
	int global_max = INT_MIN;
	for(int i = 1; i < n; i++)
	{
		if(M[i-1] < 0)
		{
			M[i] = A[i];
		}else
		{
			M[i] = M[i-1] + A[i];
		}
		if(M[i] > global_max)
		{
			global_max = M[i];
		}
	}
	return global_max;
}










































