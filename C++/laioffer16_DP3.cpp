//laioffer16_DP3.cpp

// Q1 longset continous one in unsorted array
int longestContinousOne(vector<int>& A)
{
	int global_max = INT_MIN;
	int n = A.size();
	vector<int> M(n, 0);
	M[0] = 0;
	for(int i = 1; i < n; i++)
	{
		if(A[i] == 1)
		{
			M[i] = M[i-1] + 1;
		}else
		{
			M[i] = 0;
		}
		if(M[i] > global_max)
		{
			global_max = M[i];
		}
	}
	return global_max;
}







// Q2a largeset cross arm length
int largestCrossArmLength(vector<vector<int>>& A)
{
	int n = A.size();
	int m = A[0].size();
	vector<vector<int>> M(n, vector<int>(m, 0));
	vector<vector<int>> M1(n, vector<int>(m, 0));
	vector<vector<int>> M2(n, vector<int>(m, 0));
	vector<vector<int>> M3(n, vector<int>(m, 0));
	vector<vector<int>> M4(n, vector<int>(m, 0));
	// left->right
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < m; j++)
		{
			if(j == 0)
			{
				M1[i][j] = A[j][j];
			}
			if(A[i][j] == 1)
			{
				M1[i][j] = M1[i][j-1] + 1;
			}
		}
	}
	// right->left
	for(int i = 0; i < n; i++)
	{
		for(int j = m-1; j >= 0; j--)
		{
			if(j == m-1)
			{
				M2[i][j] == A[i][j];
				continue;
			}
			if(A[i][j] == 1)
			{
				M2[i][j] = M2[i][j+1] + 1;
			}
		}
	}
	// top -> down
	for(int j = 0; i < m; j++)
	{
		for(int i = 0; j < n; i++)
		{
			if(i == 0)
			{
				M3[i][j] == A[i][j];
				continue;
			}
			if(A[i][j] == 1)
			{
				M3[i][j] = M3[i-1][j] + 1;
			}
		}
	}
	// down -> top
	for(int j = m-1; j >=0; j--)
	{
		for(int i = n-1; j >= 0; i--)
		{
			if(i == n-1)
			{
				M4[i][j] == A[i][j];
				continue;
			}
			if(A[i][j] == 1)
			{
				M1[i][j] = M1[i-1][j1] + 1;
			}
		}
	}
	int global_max = INT_MIN;
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < m; j++)
		{
			M[i][j] = min(M1[i][j], min(M2[i][j], min(M3[i][j], M4[i][j]));
			if(M[i][j] > global_max)
			{
				global_max = M[i][j];
			}	
		}
	}
	return global_max;
}







// Q3a largest subsquare surrounded by "1"
int largestSubSquareOne(vector<vector<int>>& A)
{
	int n = A.size();
	int m = A[0].size();

	vector<vector<int>>& M(n, vector<int>(m, 0));
	vector<vector<int>>& M1(n, vector<int>(m, 0));
	vector<vector<int>>& M2(n, vector<int>(m, 0));
	// step1 right -> left
	for(int i = 0; i < n; i++)
	{
		for(int j = m - 1; j>= 0; j--)
		{
			if(j == m -1)
			{
				M1[i][j] = A[i][j];
				continue;
			}
			if(A[i][j] == 1)
			{
				M[i][j] = 1 + M[i][j+1];
			}
		}
	}
	// step2 bottom -> top
	for(int j = 0 ; j <= m; j++)
	{
		for(int i = n - 1; i >= 0; i--)
		{
			if(i == n -1)
			{
				M1[i][j] = A[i][j];
				continue;
			}
			if(A[i][j] == 1)
			{
				M[i][j] = 1 + M[i-1][j];
			}
		}
	}

	int global_max = INT_MIN;
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < m; j++)
		{	
			if(A[i][j] == 1)
			{
				for(int e = min(M1[i][j], M2[i][j]); e > 0; e--)
				{
					if(M1[i+e-1][j] == e && 
						M2[i][j+e-1] == e)
					{
						M[i][j] == e;
						if(e > global_max)
						{
							global_max = e;
						}
						break
					}
				}
			}
		}
	}
	return global_max;
}



// Q4 speed up repeated query of an Arrary sum
// 用前缀和
int queryArray(vector<int>& A, int i, int j)
{
	vector<int> PathPrefixSum(A.size(), 0);
	PathPrefixSum[0] = A[0];
	for(int x = 1; x < A.size(); x++)
	{
		PathPrefixSum[x] = PathPrefixSum[x-1] + A[x];
	}
	return PathPrefixSum[j] - PathPrefixSum[i] + A[i];
}


// Q5 最大maxtix sum
// solution 1 O(n^3)
vector<vector<int>>int prefixSum(vector<vector<int>>& A)
{
	if(A.empty() || A[0].empty())
	{
		return {};
	}
	int n = A.size();
	int m = A[0].size();
	vector<vector<int>> B(n, vector<int>(m, 0));
	B[0][0] = A[0][0];
	// initlize 第一列，1D prefix 
	for(int i = 1; i < m; i++)
	{
		B[i][0] += A[i][0];
	}
	// initilize 第一行，1D prefix
	for(int j = 1; j < n; j++)
	{
		B[0][j] += A[0][j];
	}
	// initilize 后面所有的格子，表示以此点为右下角的matrix sum
	for(int i = 1; i < n; i++)
	{
		// 记录一行的1D prefix sum
		int tempDP = A[i][0];
		for(int j = 1; j < m; j++)
		{
			tempDP += A[i][j]; 
			B[i][j] = tempDP + B[i][j-1];
		}
	}
	return B;
}

vector<int> largestSumOfSubarray(vector<int>& C)
{
	if(C.empty()) return {};
	int global_left = 0;
	int global_right = 0;
	int global_max = INT_MIN;
	int temp_left = 0;
	int temp_right = 0;

	int M = 0; // temp_max,可以用一位数组，空间优化为一个，因为每次只看前一个
	for(int i = 0; i < C.size(); i++)
	{
		int temp = M + C[i];
		// DP M
		if(temp > 0)
		{
			M = temp;
			temp_right = i;
		}else
		{
			M = A[i];
			temp_left = i;
			temp_right = i;
		}

		// 找到全局最大值
		if(M > global_max)
		{
			global_max = M;
			global_left = temp_left;
			global_right = temp_right;
		}
	}
	return {global_max, global_left, global_right};
}

int maxMatrixSum(vector<vector<int>>& A)
{
	if(A.size() == 0 || B.size)
	{
		return {};
	}
	vector<int> result(5, 0);// global_Max, top, bottom, left, right
	result[0] = INT_MIN;// global_Max
	int n = A.size();
	int m = A[0].size();
	// step1 preprocess prefixSum
	vector<vector<int>> B = prefixSum(A);
	// 压扁后的数字 两行之间的和
	vector<int> C(m, 0);
	// largestSumOfSubarray 的输出
	vector<int> tempMax(3, 0); // temp_global_max, left, right
	for(int i = 0; i < n; i++)// top
	{
		for(int j = i; j < n; j++) // bottom
		{
			
			for(int c = 0; c < m; c++)
			{
				// step2.1 // 压扁，得到两行之间的和，竖着的1D的前缀sum
				C[c] = B[j][c] - B[i][c] + A[i][c];
				vector<int> tempMax = largestSumOfSubarray(C);
				if(tempMax[0] > result[0])
				{
					result[0] = tempMax[0];	//global_max
					result[1] = i;			// top
					result[2] = j;			// bottom
					result[3] = tempMax[1];	// left
					result[4] = tempMax[2];	// right
				}
			}
		}
	}
	return result;
}





































