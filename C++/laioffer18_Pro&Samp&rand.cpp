//laioffer18_Pro&Samp&rand.cpp


// Q1 shuffle card
vector<int> shuffleCard(vector<int>& A)
{
	srand(time(NULL));
	int n = A.size(); // n == 52
	for(int i = 0; i < n; i++)
	{
		int index = rand() % n;
		swap(A[n-1], A[index]);
	}
}

// Q1.2 select random k element in A
vector<int> shuffleCard(vector<int>& A, int k)
{
	srand(time(NULL));
	int n = A.size(); // n == 52
	for(int i = 0; i < k; i++)
	{
		int index = rand() % n;
		swap(A[n-1], A[index]);
	}
}





// Q2a infinite dataflow, 
int s[n];
int solu = s[0];
int i = 0;
while(i++)
{
	int r = rand() % i;//[0, i-1]
	if(r == 0)
	{
		solu = s[i];
	}
}
return solu;



// Q2b
// 无限数据流，
// 返回K个数，概率是1/i， 对前i个数
int s[n];
int solu[k] = 0;
for(int i= 0; i <= k; i++)
{
	int solu[k] = s[i];
}
int i = 0;
while(i++)
{
	int r = rand() % i;
	if(r <=k)
	{
		solu[k] = s[i];
	}
}
return solu;



// Q2c
// 无限数据流，以1/counter概率返回最大数

int max_temp = INT_MIN;
int counter = 0;
int s[n];
int solu;
int i = 0;
while(i++)
{
	if(s[0] == max_temp)
	{
		counter++;
	}else if(s[0] > max_temp)
	{
		max_temp = s[0];
		counter = 1;
	}else
	{
		counter = 1;
	}
	int r = rand() % counter + 1;//[1, counter]
	if(r == 1)
	{
		solu = max_temp;
	}
}
return solu;


// Q3a
// Random[5] -> Random[7]
int Random(int a, int b)
{
	int r1 = Random(a);
	int r2 = Random(b);
	int temp = r1 * 5 + r2;
	int range = a * a - (a * a) % b; // [0, range]
	int result = -1;
	if(temp <= range)
	{
		result = temp % 7;
	}else
	{
		result = Random(a, b);
	}
	return result;
}


// Q3b 
// Random(5) - Random(1 000 000)
int Random(int small, int big)
{
	int i = log2(big);
	while(i--)
	{
		//				5
		int x = Random(small, 2);
		result = result<<1 + x;
	}
	return result;
}
int RandomB2S(int big, int small)
{
	return big % small;
}



// Q4
// infinite data flow
// 位置一个median 中位数
// solution 1. 维持一个全局最大堆最小堆，更新
int Median(const int& x， 
			priority_queue<int>& max_heap， 							 // small  50 51 假设size不小于large
			priority_queue<int, vector<int>, greater<int>>& max_heap // large  50 50
			）
{
	if(max_heap.size() > min_heap.size())
	{
		if(x < max_heap.top())
		{
			max_heap.push(x);
			min_heap.push(max_heap.top());
			max_heap.pop();
		}else
		{
			min_heap.push(x);
		}
	}else if(max_heap.size() > min_heap.size())
	{
		if(x < max_heap.top())
		{
			max_heap.push(x);
		}else
		{
			min_heap.push(x);
			max_heap.push(min_heap.top());
			min_heap.pop();
		}
	}
	return max_heap.size() > min_heap.size() ? max_heap.top() : (max_heap.top() + min_heap.top()) / 2;
}



// solution 2 insertsort
int median(vector<int>& A, int x)
{
	A.reserve(A.size() + 1);
	for(int i = A.size() - 2; i >=0; i++)
	{
		if(A[i] >= x)
		{
			A[i+1] = A[i]; 
		}else
		{
			A[i] = x;
			break;
		}
	}
	int n = A.size();
	return n % 2 ? A[n/2] : (A[n/2]+A[(n-1)/2]) / 2 ;
}



























































