//laioffer21_JQ1.cpp

// Q1.1 deduplicate element in an array
// Solution 1
// slow: all elements to the left side of slow is the result(excluding slow)
// fast: current element
int deduplicateArray(vector<int>& A)
{
	if(A.size() == 0)
	{
		return 0;
	}
	int slow = 1;
	for(int fast = 1; fast < A.size(); fast++)
	{
		//	a a b
		//    s
		//.   f
		if(A[fast] == A[slow - 1])
		{
			continue;
		}
		A[slow++] = A[fast];
	}
	return slow;
} 

// Solution 2
// slow: all elements to the left side of slow is the result(including slow)
// fast: current element
int deduplicateArray(vector<int>& A)
{
	if(A.size() == 0)
	{
		return 0;
	}
	int slow = 0;
	for(int fast = 1; fast < A.size(); fast++)
	{
		//	a a b
		//  s
		//.     f
		if(A[fast] == A[slow])
		{
			continue;
		}
		A[++slow] = A[fast];
	}
	return slow + 1;
}


 // Q1.2 最多保留两个
// 1 1 1 2 2 3
//     s
//.    f
// A[f] ? A[s-2]
// slow：左边不包括slow的是要返回的值
// fast: current
int deduplicateArray2(vector<int>& A, int k)
{
	if(A.size() <= k)
	{
		return A.size();
	}

	int slow = k;
	for(int f = 0; f < A.size(); f++)
	{
		if(A[f] != A[slow - k]) // 这个最关键，因为数组一已经是sorted
		{
			continue;
		}
		A[slow++] = A[f];
	}
	return slow;
}



// Q1.3
// 删除所有重复元素，一个也不留
// 1 1 1 2 3 3 -> s
// s
//       f1
//         f2
// s 左边为返回值，not including slow
int deduplicateArrayALL(vector<int>& A)
{
	int slow = 0;
	int f2 = 0;
	while(f2 < A.size())
	{
		int f1 = f2;
		while(f2 < A.size() && A[f1] == A[f2])
		{
			f2++;
		}
		if(f2 - f1 == 1)// 说明相邻两个数不重复
		{
			A[slow++] = A[f1];
		}
	}
	return slow;
}


// Q1.4
// unsorted array, 反复消除重复元素，俄罗斯方块

string removeDuplicateCharRepeatly(string& str)
{
	// 显示的申请一个stack
	string S;
	int i = 0;
	while(i < str.size())
	{
		if(S.empty() || str[i] != S.back())
		{
			s.push_back(str[i]);
			i++;
		}else
		{
			while(i < str.size() && str[i] == S.back())
			{	i++;
			
			}
			S.pop_back();
		}
	}
	return  S;
}



// 1.5
// array random number, 0 都挤到最右边， 其他数字【顺序可变】
// 1 2 3 4 2 3 0 0 0 1 -> 1 2 3 4 2 3 1 0 0 0 
// l 				 r
//
// left : 它的左边都非0
// right：它的右边都是0
// [l, r]: 没找到的

int pushZeros2Right(vector<int>& A)
{
	int l = 0;
	int r = A.size() - 1;
	while(l <= r) // r l 错过
	{
		if(A[l] != 0)
		{
			l++;
		}else if(A[r] == 0)
		{
			r--;
		}else
		{
			swap(A[l], A[r]);
			l++
			r--;
		}
	}
	return l;
}


// 1.5.2 
// array random number, 0 都挤到最右边， 其他数字顺序【保持一致】
// 1 2 3 4 2 3 0 0 0 1 -> 1 2 3 4 2 3 1 0 0 0 
// s
// f
void pushZeros2Right(vector<int>& A)
{
	if(A.empty()) return;
	int s = 0;
	int f = 0;
	while(f < A.size())
	{
		if(A[f] != 0)
		{
			A[s++] = A[f++];
		}else
		{
			f++;
		}
	}
	while(s < A.size())
	{
		A[s] = 0;
	}
}



// 									Q2 array number comparisons

// Q2.1 用最小K次比较，得到最大最小值
// 1 2 3 4 5 6 7 8
// 1 3 5 7	small
// 2 4 6 8	big
// O(1.5n)
vector<int> compareArray(vector<int>& A)
{
	vector<int> small;
	vector<int> big;
	int i = 0;
	while(i < A.size() -1)
	{
		if(A[i] < A[i+1])
		{
			small.push_back(A[i]);
			big.push_back(A[i+1]);
		}else
		{
			small.push_back(A[i+1]);
			big.push_back(A[i]);
		}
		i +=2;
	}
	int s = INT_MAX;
	int b = INT_MIN;
	for(auto it : small)
	{
		if(it < s)
		{
			s = it;
		}
	}

	for(auto it : big)
	{
		if(it > b)
		{
			b = it;
		}
	}
	return {s, b};
}


// Q2.2 找最大和第二大的数，最少的比较次数


// Q3 2D array print in spiral order or rotate

// Q3.1 spiral order 

// Q3.2 rotate 90





// Q4 BT
// Q4.1 分层打印 BT

// Q4.2 zig-zag


// Q5 LCA





























