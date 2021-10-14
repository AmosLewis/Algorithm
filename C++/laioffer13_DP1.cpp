//laioffer13_DP1.cpp


// 2 Longest Ascending Subarray
// A  7 2 3 4 1 2 7 8 6
// M  1 1 2 3 1 2 3 4 1
// 用一个数组M记录 
// 	从 0th - ith 元素中
//  以 当前元素【结尾】的
// 【最长】 【升序】 子序列的
// 【长度】 
int longestAscendingSubarray(vector<int>& A)
{
	// M means form 0th to ith element, 
	// the longeset Ascending Subarray ended with current element
	vector<int> M(A.size(), 0);
	M[0] = A[0];
	int global_max = -1;
	for(int i = 1; i < A.size(); i++)
	{
		if(A[i] <= A[i-1])
		{
			M[i] = 1;
		}else
		{
			A[i] = A[i-1] + 1;
		}
	}
}


// 3 Max rope productivity
// solution 1
// Time O(n^2)
int cutRope(int n)
{
	vector<int> M(n+1,0);// 第index长度，最大的乘积
	M[0] = 0;
	M[1] = 0;
	for(int i = 1; i <= n; i++) // 一层一层加绳子长度
	{
		int curMax = i;
		for(int j = 1; j < i / 2; j++)//左大段的所有可能性
		{
			curMax = max(max(curMax, M[j]), max(i - curMax, M[i - curMax]));
		}
		M[i] = curMax;
	}
	return M[n];
}


// solution 2
int curRope(int n)
{
	vector<int> M(n+1, 0);
	M[0] = 0;
	M[1] = 0;
	for(int i = 1; i <= n; i++)// 一层一层加绳子长度
	{
		int curMax = 0; // 每个右小段都会得到一个最大值，找其中最大的
		for(int j = n - 2; j > 0; j--)// 遍历所有右小段可能性，不可分割部分的长度
		{
			int curMax = max(curMax, max(n - j, M[n - j]) * i);
		}
		M[i] = curMax;
	}
	return 
}

//Solution 3
// O(n!)
int getMaxProduct(int n)
{
	if(n <= 1)
	{
		return 0;
	}
	int maxProduct = 0; // 每个右小段都会得到一个最大值，找其中最大的
	for(int i = 1; i < n; i++) // 固定住右小段
	{
		int leftBest = max(n - i, getMaxProduct(n - i));//
		int maxProduct = max(maxProduct, leftBest * i);
	}
	return maxProduct;
}


// Jump Game
// A = [2, 3, 1, 1, 4]
// 从右向左看
bool jumbGame(vector<int>& A)
{
	bool flag = 0;
	vector<bool> M(A.size(), false); // M代表从当前点是否可以跳出去
	for(int i = A.size() - 1; i >=0; i--) // 从右向左遍历每一个点
	{
		int step = A[i];
		for(j = 0; j <= min(A.size() - i, step); j++) // 看这个点右边可到达的M是否有满足True的
		{
			if(M[i + j] == true)
			{
				M[i] = true;
			}
		}
	}
	return M[0];
}

















