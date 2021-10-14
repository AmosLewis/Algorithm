void selectionSort(vector<int>& A, int n)
{
	if(A.size() == 0) return;
	int global;
	for(int i = 0; i < n - 1; i++)
	{
		global = i;	// index of first element on the right side(unsorted)
		for(int j = i + 1; j < n; j++)
		{
			if(a[j] < a[global])
			{
				global = j;	
			}
		}
		// 左边是已经排序好的 | 右边的最小值放到右边的最左边
		//				 i 				global
		swap(A[i], A[global]);
	}
}

// follow up : 模拟selection sort, 对一个stack 排序， 用另外两个stack,有重复元素
vector<int> 2stackSort(stack<int>& A)
{
	int n = A.size();
	stack<int> st1;
	vector<int> st2;
	while(!A.empty())
	{
		int global_min = INT_MIN;
		// 1 把A放入st1  找到global_min
		while(!A.empty())
		{
			int cur = A.top();
			if(global_min < cur)
			{
				global_min = cur;
			}
			st1.push(cur);
			A.pop();
		}

		while(!st1.empty())
		{
			// 2 st1放回A， 除了global_min,因为有重复元素，可能放了好多次
			if(st1.top() != global_min)
			{
				A.push(st1.top());
			}else
			{
				// 3 global_min 放入st2作为结果
				st2.push_back(global_min);
			}
			st1.pop();
		}
	}
	return st2;
}


vector<int> mergeSort(vector<int>& a, int left, int right)
{
	// Time O(nlogn)
	// Space O(n)
	vector<int> solution;
	if(left == right)
	{
		solution.push_back(a[left]);
		return solution;
	}
	int mid = left + (right- left)/2;
	vector<int> sol1 = mergesort(a, left, mid);
	vector<int> sol2 = mergesort(a, mid+1, right);
	solution = combine(sol1, sol2);
	return solution;
}
vector<int> combine(vector<int>& V1, vector<int>& V2)
{
	vector<int> res;
	int i = 0, j = 0;
	int n1 = V1.size() - 1;
	int n2 = V2.size() - 1;
	while(i <= n1 && j <= n2)
	{
		if(V1[i] < V2[j])
		{
			res.push_back(V1[i++]);
		}else
		{
			res.push_back(V2[j++]);
		}
	}
	while(i <= n1)
	{
		res.push_back(V1[i++]);
	}
	while(j <= n2)
	{
		res.push_back(V2[i++]);
	}
	return res;
}


// 2.1 a1b2c3d4-> abcd1234
string mergesort(string& A, int left, int right)
{
	string res;
	if(left == right)
	{
		return res.push_back(A[left]);
	}
	int mid = left + (right - left)/2
	string sub1 = mergesort(A, left, mid);
	string sub2 = mergesort(A, mid + 1, right);
	return combine(sub1, sub2);
}
string combine(string& str1, string& str2)
{
	string res1;// 1234
	string res2;// abcd
	int i = 0, j = 0;
	int n1 = str1.size() - 1;
	int n2 = str2.size() - 1;
	while(i < n1 && j < n2)
	{
		if(isDigit(str1[i]) && isDigit(str2[j]))
		{
			if(str1[i] < str2[j])
			{
				res1.push_back(str1[i++]);
			}else{
				res1.push_back(str2[j++]);
			}
		}else(isAlpha(str1[i]) && isDigit(str2[j]))
		{
			if(str1[i] < str2[j])
			{
				res1.push_back(str1[i++]);
			}else{
				res1.push_back(str2[j++]);
			}
		}else if(isDigit(str1[i]))
		{
			res1.push_back(str1[i]);
			res2.push_back(str2[j]);
		}else
		{
			res1.push_back(str2[i]);
			res2.push_back(str1[j]);
		}
	}
	while(i <= n1)
	{
		if(isAlpha(str1[i]))
		{
			res1.push_back(str1[i++]);
			res2.push_back(str1[i++]);
		}else
		{
			res1.push_back(str1[i++]);
			res2.push_back(str1[i++]);
		}
	}

	while(j <= n1)
	{
		if(isAlpha(str2[j]))
		{
			res1.push_back(str1[j++]);
			res2.push_back(str1[j++]);
		}else
		{
			res1.push_back(str1[j++]);
			res2.push_back(str1[j++]);
		}
	}

	return res2 + res1;
}


// 2.2 ABCD1234 -> A1B2C3D4
// l        lm.     m.      rm. r
// A 	B |	C 	D |	1 	2 |	3 	4 	
void mergesort(string& A, int left, int right)
{
	if(right - left <= 1)
	{
		return;
	}
	int size = right - left + 1;
	int lm = left + size/4;
	int m = left + size / 2;
	int rm = left + size * 3 / 4;

	reverse(A, lm, m -1);
	reverse(A, m, rm -1);
	reverse(A, l, rm -1);

	mergesort(A, left, left + 2 * (lm - left) - 1);
	mergesort(A, left + 2 * (lm - left), right);
}
void reverse(A, l, r)
{
	while(l <= r)
	{
		swap(A[l], B[r]);
	}
}


// 2.3 k way merge
ListNode* mergeKSortedList(vector<ListNode*> v,int left, int right)
{
	if(left == right) return v[left];

	int mid = left + (right - left)/2;

	ListNode* l1 = mergeKSortedList(v, left, mid);
	ListNode* l2 = mergeKSortedList(V, mid + 1, right);
	return merge2SortedList(l1, l2);
}
ListNode* merge2SortedList(ListNode* l1, ListNode* l2)
{
	ListNode dummy(0);
	ListNode* head = &dummy;
	while(l1 && l2)
	{
		if(l1->val < l2->val)
		{
			head->next = l1;
		}else
		{
			head->next = l2;
		}
		head = head->next;
	}
	if(l1)
	{
		head->next = l1;
	}
	if(l2)
	{
		head->next = l2;
	}
	return dummy.next;
}


// 2.4 count array (number of smaller item on the right)
// 9 8 7 6 5 4 11 3
vector<pair<int, int>> findSmaller(vector<int>& A, int left, int right)
{
	if(left == right)
	{
		return {make_pair(A[left], 0)};
	}

	int mid = left + (right - left) / 2;
	auto sub1 = findSmaller(A, left, mid);
	auto sub2 = findSmaller(A, mid + 1, right);

	return combine(sub1, sub2);
}
vector<pair<int, int>> combine(vector<pair<int, int>>& sub1, vector<pair<int, int>>& sub2)
{
	vector<pair<int, int>> res;
	int n1 = sub1.size();
	int n2 = sub2.size();
	int i = 0;
	int j = 0;
	while(i < n1 && j < n2)
	{
		if(sub1[i].first < sub2[j].first)
		{
			sub1[i].second += j;
			res.push_back(sub1[i++]);
		}else
		{
			res.push_back(sub2[j++])
		}
	}
	while(i < n1)
	{
		sub1[i].second +=j;
		res.push_back(sub1[i++]);
	}
	while(j < n2)
	{
		res.push_back(sub2[j++]);
	}
	return res;
}


void quickSort(vector<int>& A, int left, int right)
{
	if(left > right)
	{
		return;
	}

	int s = left;
	int e = right;
	int mid = left + (right - left) / 2;
	int pivot = A[mid];
	while(left <= right)
	{
		while(left <= right && A[left] < pivot)
		{
			left++;
		}
		while(left <= right && A[right] > pivot)
		{
			right--;
		}
		if(left <= right)
		{
			swap(A[left++], A[right--]);
		}
	}
	if(s < right)
	{
		quickSort(A, s, right);
	}
	if(left < e)
	{
		quickSort(A, left, e);
	}
}

// Follow up: 
// 2.4 Rainbow sort
// abaacbcccabb -> aaaa bbbb xxxx cccc
// aaaa bbbb xxxx cccc
//      i.   j. k
void rainbowSort(vector<char>& A)
{
	int i = 0;
	int k = A.size() - 1;
	while(j < A.size() && k >= 0)
	{
		if(A[j] == 'a')
		{
			swap(A[i++], A[j++]);
		}else if(A[j] == 'b')
		{
			j++;
		}else if(A[j] == 'c')
		{
			swap(A[j++], A[k--]);
		}
	}
}


//laioffer2 Recursion1 binary search
// fibo
int Finbo(int n)
{
	if(n == 0)
	{
		return 0;
	}else if( n == 1)
	{
		return 1;
	}

	return Finbo(n-1) * Finbo(n-2);
}

// 这只是假定b是正数字，如果b是负数呢 a是0呢
int power(int a, int b)
{
	if(b == 0)
	{
		return 1;
	}

	int half_result = power(a, b/2);
	if(b % 2 == 0)
	{
		return half_result * half_result;
	}else
	{
		return half_result * half_result * a;
	}
}
// b 1000 500 125 ... 0
// time = O(log(b))
// space = O(log(b))





// 3 4 5 6 7 8 : 6
// 法1 一波流 l <= r + mid+1/mid-1
int binary_search(vector<int>& A, int target)
{
	if(A.empty())
	{
		return -1;
	}

	int l = 0;
	int r = A.size() - 1;
	while(l <= r) // {5} 5
	{
		int mid = left + (right - left) / 2;
		if(A[mid] == target)
		{
			return mid;
		}else if(A[mid] < target)
		{
			l = mid + 1; // {5}, 7
		}else
		{
			r = mid - 1; // {5}, 3
		}
	}
	return -1;
}

// 法2 start + 1 < end + mid + post processing
int binary_search(vector<int>& nums, int target)
{
	if(nums.size() == 0)
	{
		return -1;
	}
	int start = 0, end = nums.size() - 1;
	while(start + 1 < end)
	{
		int mid = start + (end - start)/2;
		if(target == nums[mid])
		{
			return mid;
		}else if(target < nums[mid])
		{
			end = mid;
		}else
		{
			start = mid;
		}
	}
	// post processing
	if(nums[start] == target)
	{
		return start;
	}
	if(nums[end] == target)
	{
		return end;
	}
	return -1;
}

bool findtarget2D(vector<vector<int>> matrix), int target)
{
	if(matrix.size() == 0 || martix[0].size() == 0)
	{
		return false;
	}

	int row = matrix.size();
	int col = matrix[0].size();
	int start = 0, end  = m * n - 1;
	while(start <= end)
	{
		int mid = start + (end - start)/2;
		int r = mid / col;	// only difference between 1d binary search
		int c = mid % col;
		if(matrix[r][c] == target)
		{
			return true;
		}else if(matrix[r][c] < target)
		{
			start = mid + 1;
		}else
		{
			end = mid - 1;
		}
	} 
	return false;
}

// variation 1.1
int binarySearchClosest(vector<int>& nums, target)
{
	if(nums.size() == 0)
	{
		return -1;
	}
	int start = 0, end = nums.size() - 1;
	while(start + 1 < end)
	{
		int mid = start + (end - start)/2;
		if(target == nums[mid])
		{
			return mid;
		}else if(target < nums[mid])
		{
			end = mid;	// mid + 1 不对 ,若mid = target, mid+1 会被跳过
		}else
		{
			start = mid;
		}
	}
	// post processing
	if(abs(nums[start] - target) <= abs(nums[end] - target))
	{
		return start;
	}else
	{
		return end;
	}
}
// // variation 1.1 traditional 版本，不用
// int binarySearchClosest(vector<int>& nums, target)
// {
// 	if(nums.size() == 0)
// 	{
// 		return -1;
// 	}
// 	int start = 0, end = nums.size() - 1;
// 	while(start <=  end)
// 	{
// 		int mid = start + (end - start)/2;
// 		if(target == nums[mid])
// 		{
// 			if(mid == 0 || nums[mid - 1] < target)
// 			{
// 				return mid;
// 			}else // nums[mid - 1] == target
// 			{
// 				end = mid - 1;
// 			}
// 		}else if(target < nums[mid])
// 		{
// 			end = mid;	// mid + 1 不对 ,若mid = target, mid+1 会被跳过
// 		}else
// 		{
// 			start = mid;
// 		}
// 	}
// 	// post processing
// 	if(abs(nums[start] - target) <= abs(nums[end] - target))
// 	{
// 		return start;
// 	}else
// 	{
// 		return end;
// 	}
// }


// variation1.2 find first occurance of target
int findFirstOccurance(vector<int>& A, int target)
{
	if(A.empty())
	{
		return -1;
	}
	int l = 0; 
	int r = A.size() - 1;
	while(l + 1 < r) // l neighbors r
	{
		int mid = l + (r - l) / 2;
		if(A[mid] == target)
		{
			r = mid; // do not stop here
		}else if(A[mid] < target)
		{
			l = mid + 1; // mid
		}else
		{
			r = mid - 1; // mid
		}
	}

	if(A[l] == target)
	{
		return l;
	}
	if(A[r] == target)
	{
		return r;
	}
	return -1;
}


// v1.3 find last occurance of target
int findLastOccurance(vector<int>& A, int target)
{
	if(A.empty())
	{
		return -1;
	}
	int l = 0; 
	int r = A.size() - 1;
	while(l + 1 < r)
	{
		int mid = l + (r - l) / 2;
		if(A[mid] == target)
		{
			l = mid; // 这里和first 不一样， r变l
		}else if(A[mid] < target)
		{
			l = mid + 1; // mid
		}else
		{
			r = mid - 1; // mid
		}
	}

	if(A[r] == target)// 这里和first 不一样， l变r
	{
		return r;
	}
	if(A[l] == target) // 这里和first 不一样， r变l
	{
		return l;
	}
	return -1;
}


// Java 3 class
// v1.4
// find the K closet number of target in sorted array
vector<int> findKCloest(vector<int> nums, int target, int k)
{
	// step1: binary search the largest the number smaller than target, O(logn)
	// step2: expand from the number with 2 pointer,O(k)
	if(nums.size() == 0 || k == 0)
	{
		return {};
	}

	// left is the larget smaller/equal element
	// right = left+1
	// this two should be the cloest to the target
	int left = largestSmallerEqual(nums, target);
	int right = left + 1;

	// merge operation
	// expand from the central
	vector<int> result(k, 0);
	for(i = 0; i < k; i++)
	{
		// move left
		// case 1: right pointer out of boundary
		// case 2: right pointer not out of boundary
		// left pointer is not out of boundary  but num[left] is closer
		if(right >= nums.size() || left >= 0 && target - nums[left] <= nums[right] - target)
		{
			result[i] = nums[left--];
		}else
		{
			result[i] = nums[right++];
		}
	}
} 
int largestSmallerEqual(num, target)
{
	if(nums.size() == 0)
	{
		return -1;;
	}
	int start = 0, int end = nums.size();
	while(start < end - 1)	// start end 相邻停
	{
		int mid = start + (end - start) / 2;
		if(target == nums[mid])
		{
			return mid;
		}else if(target > nums[mid])
		{
			start = mid;
		}else 
		{
			end = mid;
		}
	}
	// post process
	// target equal / smaller than the smallest of nums, return start
	if(target <= nums[start])
	{
		return start;
	}
	// target equal / larger than the larget of nums. return end
	if(num[end] <= target)
	{
		return end;
	}

	return start;
}


// v2.0
// sorted dictionary with unknown size
// {1 2 3 999 ... 10000 ....} 9999
//  -
//  --
//. ----
//  --------
//  ----------------
//  --------------------------------
// 答案不对,不知道怎么写越界的情况
// 以 2 time 向外跳， 对[0, 2^r] binary search
// 以 10 times向外跳, 对[0, 10^r] binary search, 通过计算，这个更好

bool findTargetUnknowDic(vector<int>& A, int target)
{
	if(A.empty())
	{
		return;
	}
	int i = 1;
	while(A[pow(2,i)])
	{
		if(binary_search(A, target, pow(2, i-1), pow(2, i)))
		{
			return true;
		}
		i++;
	}
	return false;
}
bool binary_search(vector<int>& A, int target, int l, int r)
{
	if(A[r] != nullptr)
	{
		while(l <= r)
		{
			int mid = l + (r - l) / 2;
			if(A[mid] == target)
			{
				return true;
			}else if(A[mid] < target)
			{
				l = mid + 1;
			}else
			{
				r = mid - 1;
			}
		}
		return false;
	} 

	if(A[r] == nullptr)
	{
		while(l <= r)
		{
			int mid = mid = l + (r - l) / 2;
			if(A[mid] == target)
			{
				return true;
			}else if(A[mid] < target)
			{
				l = mid + 1;
			}else if(A[mid] > target)
			{
				r = mid - 1;
			}else if(A[mid] == nullptr)
			{
				r = mid - 1;
			}
		}
		return false
	}

}















