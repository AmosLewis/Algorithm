//practice1.cpp

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

// selection  sort follow up 1
vector<int> 2stackSelectionSort(stack<int>& A)
{
	if(A.empty())
	{
		return {};
	}

	stack<int> st1;
	vector<int> st2;

	while(!A.empty())
	{
		int global_min = INT_MIN; // ascending
		// 1 stack0 -> stack1 : find global min
		while(!A.empty())
		{
			if(A.top() < global_min)
			{
				global_min = A.top();
			}
			st1.push(A.top());
			A.pop();
		}

		// 2 stack1 -> stack0 : recover
		// 3		-> stack1 : result
		while(!st1.empty())
		{
			if(st1.top() != global_min) // recover
			{
				A.push(st1.top());
			}else
			{
				st2.push_back(global_min); // result
			}
			st1.pop();
		}
	}
	return st2;
}


// selection sort follow up 2
// use only one additional stack
vector<int> 1stackSelectionSort(stack<int>& A)
{
	if(A.empty())
	{
		return {};
	}
	vector<int> st1;
	while(!A.empty())
	{
		int global_min = INT_MIN;
		int count;
		// 1 A -> st1 find global_min
		while(!A.empty())
		{
			if(A.top() < global_min)
			{
				global_min = A.top();
				count = 1;
			}else if(A.top() == global_min)
			{
				count++;
			}
			st1.push_back(A.top());
			A.pop();
		}
		//2 st1 *** -> A : recover
		//  str [1 | ***]
		while(!st.empty() && st1.top() >= global_min) // 这里与上面2 stack 不同
		{
			if(st1.top() > global_min)
			{
				A.push(st1.top());
			}
			st1.pop();
		}
		//3 count global_min -> st1 : result
		while(count)
		{
			st1.push_back(global_min);
			count--;
		}
	}
	return st1;
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


// 2.4 find number of smaller item on the right of current item
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


// Time O(nlogn) worest case O(n)
// [0,i) < pivot
// (j, n-1] > pivot
// [i,j] 未知区域
void quickSort(vector<int>& A, int left, int right)
{
	if(left >= right)
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
	if(s <= right)
	{
		quickSort(A, s, right);
	}
	if(left <= e)
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


// 2d sorted
// 1  2  3  4  5
// 6  7  8  9  10
// 11 12 13 14 15
// target 7
bool findTarget2D(vector<vector<int>>& A, int target)
{
	if(A.empty() || A[0].empty())
	{
		return false;
	}

	int n = A.size();
	int m = A[0].size();
	int l = 0;
	int r = n * m - 1;

	while(l <= r)
	{
		int mid = l + (r - l) / 2;
		int r = mid / m; // 这两句是关键
		int c = mid % m; // 这两句是关键
		if(A[r][c] == target)
		{
			return true;
		}else if(A[r][c] < target)
		{
			l = mid + 1;
		}else
		{
			r = mid - 1;
		}
	}
	return false;
}


// v1.1 find item cloeset to target
int findCloest(vector<int>& A, int target)
{
	if(A.empty())
	{
		return -1;
	}

	int l = 0, r = A.size() - 1;
	while( l + 1 <  r) // [l,r]停下
	{
		int mid = l + (r - l) / 2;
		if(A[mid] == target)
		{
			return mid;
		}else if(A[mid] < target)
		{
			l = mid;
		}else
		{
			r = mid;
		}
	}
	if(abs(A[l] - target) < abs(A[r - target]))
	{
		return l;
	}else
	{
		return r;
	}
}



// v1.2 find first occurance of target
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



// v1.4 无重复元素 k closet
vector<int> findKCloest(vector<int>& A, int target, int k)
{
	if(A.empty() || A.size() < k)
	{
		return {};
	}

	// 比target小或等，最大的数
	int l = findSmallerEqual(A, target); // O(logn)
	int r = l + 1;

	vector<int> res(k, 0);
	// expand from central
	for(int i = 0; i < k; i++) // O(k)
	{
		if(r >= A.size() || l >= 0 && target - A[l] <= A[r] - target)
		{
			res[i] = A[l--];
		}else
		{
			res[i] = A[r++];
		}
	}
	return res;
}
int findSmallerEqual(vector<int>& A, int target)
{
	int l = 0; 
	int r = A.size() - 1;
	while(l + 1 < r)
	{
		int mid = l + (r - l) / 2;
		if(A[mid] == target)
		{
			return mid;
		}else if(A[mid] < target)
		{
			l = mid;
		}else
		{
			r = mid;
		}
	}
	//       1 2 3 8 9
	//  0.5. l r
	if(target <= A[l])
	{
		return l;
	}
	//       1 2 3 8 9
	//             l r 10
	if(target >= A[r])
	{
		return r;
	}
	// 1 2 3   8 9
	//     l 4 r
	return l;
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
// 这题没写出答案



// laioffer3 
// implement queue with 2 stack
template <class T>
class MyQueue
{
public:
	void push(T a)
	{
		s1.push(a);
	}

	T pop()
	{
		if(s2.empty() && s1.empty())
		{
			return -1;
		}

		if(s2.empty())
		{
			while(!s1.empty())
			{
				s2.push(s1.top());
				s1.pop();
			}
		}
		T a = s2.top();
		s2.pop();
		return a;
	}
private:
	stack<T> s1;
	stack<T> s2;
}


// 2. 2 stack -> min
class MinStack{
public:
	MinStack():global_min(INT_MAX){}
	void add(int a)
	{
		s1.push(a);
		if(a < global_min)
		{
			global_min = a;
		}
		s2.push(global_min);
	}
	int remove()
	{
		int temp = s1.top();
		s1.pop();
		s2.pop();
		global_min = s2.top();
		return temp;
	}
private:
	stack<int> s1;
	stack<int> s2;
	int global_min;
}
// follow up
// a lot of duplicate, optimize space
// s2 store pari<int, int>

class minStackRepeat{
public:
	void add(int a)
	{
		s1.push(a);
		if(a < global_min)
		{
			s2.push(make_pair(a, s1.size()));// 这句话是重点，保存遇到该最小值时候的s1的大小
			global_min = a;
		}
	}
	int remove()
	{
		int temp = s1.top();
		if(s2.top().second == s1.size())// 这句话是重点， 保存
		{
			s2.pop();
			global_min = s2.top().second;
		}
		return temp;
	}
private:
	stack<int> s1;
	stack<pair<int, int>> s2; // [val, startindex]
	int global_min;
}

// 2stack selection sort

// 3 stack -> deque
// half half, s3 buffer





// 												LinkedList
// recursion 
ListNode* reverseList(ListNode* head)
{
	if(head == nullptr || head->next == nullptr)
	{
		return head;
	}

	ListNode* next = head->next;
	LiseNode* new_head = reverseList(head->next);

	next->next = head;
	head->next = cur;
	return new_head;
}
// iteration
ListNode* reverseList(ListNode* head)
{
	if(head== nullptr || head->next == nullptr)
	{
		return head;
	}

	ListNode* pre = nullptr;
	ListNode* cur = head;
	while(cur)
	{
		ListNode* next = cur->next; // 新建一个节点
		cur->next = pre;
		pre = cur;
		cur = next;
	}
	return pre;
}


// find the middle node of list
ListNode* findMiddle(ListNode* head)
{
	if(head == nullptr)
	{
		return head;
	}
	ListNode* s = head;
	ListNode* f = head;
	while(f->next != nullptr & f->next->next != nullptr) // 这里要注意
	{
		s = s->next;
		f = f->next->next;
	}
	return s;
}


// find if circle
bool ifCircle(ListNode* head)
{
	ListNode* s = head;
	ListNode* f = head;
	while(s && f && f->next)// 这个比较重要， 和上面的不大一样，不是f->next->next
	{
		if(f == s)
		{
			return true;
		}
		f = f->next->next;
		s = s->next;
	}
	return false;
}


// insert a node in list
ListNode insertNode(ListNode* head, int val)
{
	LitNode* l1 = new ListNode(val);
	if(head == nullptr)
	{
		return l1;
	}

	if(l1->val < head->val)
	{
		l1->next = head;
		return l1;
	}

	ListNode* pre = head;
	ListNode* cur = head->next;
	while(pre && cur)
	{
		if(pre->val < l1->val && l1->val < cur->val)
		{
			pre->next = l1;
			l1->next = cur;
			return head;
		}
		pre = pre->next;
		cur = cur->next;
	}

	pre->next = l1;
	return head;
}


// merge two linkedlist
ListNode* mergesort(ListNode* l1, ListNode* l2)
{
	ListNode dummy(0);
	ListNode* head = &dummy;
	while(l1 && l2)
	{
		if(l1->val <= l2->val)
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

// patition list
ListNode* patition(ListNode* head, int target)
{
	if(!head)
	{
		return head;
	}

	ListNode dummy1(0);
	ListNode dummy2(0);
	ListNode* small = &dummy1;
	ListNode* large = &dummy2;

	while(head)
	{
		if(head->val < target)
		{
			small->next = head;
			small = small->next;
		}else
		{
			large->next = head;
			large = large->next;
		}
		head = head->next;
	}
	small->next = dummy2.next;
	large->next = nullptr;
	return dummy1.next;
}


// laioffer 4  BST
// space time O(n), 最坏的是linkedlist
int getHeight(TreeNode* root)
{
	if(!root)
	{
		return 0;
	}
	int left = getHeight(root->left) + 1;
	int right = getHeight(root->right) + 1;

	return max(left, right);
}

// time O(n*logn)
bool isBalanced(TreeNode* root)
{
	if(root == nullptr)
	{
		return true;
	}

	int lh = getHeight(root->left);// O(n)
	int rh = getHeight(root->right);// O(n)

	if(abs(lh - rh) > 1)
	{
		return false;
	}else
	{
		return isBalanced(root->left) && isBalanced(root->right);
	}
}
// better solution
// O(n)
bool isBalanced(TreeNode* root)
{
	bool flag = true;

	int h = helper(root, flag); // 全局变量记录isbalanced,返回值是高度

	return flag;
}
int helper(TreeNode* root, bool& flag)
{
	if(root == nullptr)
	{
		return 0;
	}

	int lh = helper(root->left, flag) + 1;
	int rh = helper(root->right, flag) + 1;

	if(abs(lh - rh) > 1)
	{
		flag = false;
		return -1;
	}

	return max(lh, rh) + 1;
}



// Tree is symmetrical
// Time O(n/2)
// space O(n) 有可能不balance
bool isSymatric(TreeNode* root)
{
	if(root == nullptr)
	{
		return true;
	}
	return isSymmetrical(root->left, root->right);
}
bool isSymmetrical(TreeNode* left, TreeNode* right)
{
	if(left == nullptr && right == nullptr)
	{
		return true;
	}else if(left == nullptr || right == nullptr)
	{
		return false;
	}else if(left->val != right->val)
	{
		return false;
	}

	return isSymmetrical(left->right, right->left) &&
		isSymmetrical(left->left, right->right);
}



// 
bool isIdentical(TreeNode* root)
{
	if(root == nullptr)
	{
		return true;
	}

	return isIdentical(root->left, root->right);
}
bool isIdentical(TreeNode* n1, TreeNode* n2)
{
	if(n1 == nullptr && n2 == nullptr)
	{
		return true;
	}else if(n1 == nullptr || n2 == nullptr)
	{
		return false;
	}else if( n1->val != n2->val)
	{
		return false;
	}
	return isIdentical(n1->left, n2->left)&&isIdentical(n1->right, n2->right) ||
	isIdentical(n1->left, n2->right)&&isIdentical(n1->right, n2->left);
}
// 4叉树
// height log_2(n)
// 1 2 4 16 
// 1 4 16
// 4^log_2(n) = 2^2(log_2(n)) = O(n^2)


//
bool isBST(TreeNode* root)
{
	if(root == nullptr)
	{
		return true;
	}

	return helper(root, INT_MIN, INT_MAX);
}

bool helper(TreeNode* root, int min, int max)
{
	if(root == nullptr)
	{
		return true;
	}

	if(root->val >= max || root->val <= min)
	{
		return false;
	}
	return helper(root->left, min, root->val) && helper(root->right, root->val, max);
}


void inorderPrintRangeBST(TreeNode* node, int k1, int k2)
{
	if(node == nullptr)
	{
		return;
	}

	if(k1 < node->val) // 加一个是否向左走的判断很重要，不满足直接剪枝
	{
		inorderPrintRangeBST(node->left, k1, k2);
	}
	if(k1 <= node->val && node->val <= k2) // 满足条件再打印
	{
		cout<<node->val<<endl;
	}
	if(node->val < k2)
	{
		inorderPrintRangeBST(node->right, k1, k2);
	}
}


TreeNode* insertBST(TreeNode* root, int target)
{
	if(root == nullptr)
	{
		return new TreeNode(target);
	}

	if(target < root->val)
	{
		root->left = insertBST(root->left, target);
	}
	if(target > root->val)
	{
		root->right = insertBST(root->right, target);
	}
	return root;
}


// recursion II: remove redudant operation
// 加一个外层函数处理root的返回问题
TreeNode* insertBST(TreeNode* root, int target)
{
	// 在外层函数处理没有
	if(root == null)
	{
		return new TreeNode(target);
	}
	insertBSThelper(TreNode* root, target);
	return root;
}
void insertBSThelper(TreeNode* root, int target)
{
	if(target == root->val)
	{
		return;
	}else if(target < root->val)
	{
		if(!root->left)// 左边为空
		{
			root->left = new TreeNode(target);
			return;
		}else{
			insertBST(root->left, target);
		}
		
	}else if(root->val < target)
	{
		if(!root->right) // 右边为空
		{
			root->right = new TreeNode(target);
		}else{
			insertBST(root->right, target);
		}
	}
}

// 方法3:iterative
// 给出父子节点
TreeNode* insertBST(TreeNode* root, int target)
{
	TreNode* new_node = TreeNode(target);
	if(root == nullptr)
	{
		return new_node;
	}

	// 将root 保存下来，另外起一个cur进行插入操作
	// 所以这里可以像recursion	II一样进行另外起一个helper函数
	// 下面这个循环就相当于 recursionII的helper函数
	TreNode* cur = root;
	while(cur != nullptr && target != cur->val)
	{
		if(target < cur->val)
		{
			if(cur->left == nullptr)
			{
				cur->left = new_node;
			}
			cur = cur->left;
		}
		if(cur->val < target)
		{
			if(cur->right == nullptr)
			{
				cur->right = new_node;
			}
			cur = cur->right;
		}
	}
	// 返回没有改变的root
	return root;
}






vector<int> kSmallest(vector<int>& A, int k)
{
	vector<int> res;
	if(k.size() < k)
	{
		return res;
	}

	priority_queue<int, vector<int>, [](const int a, const int b) {
		return a < b;
	}> max_heap;

	for(auto it:A)
	{
		if(max_heap.size() < k)
		{
			max_heap.push(it);
		}else
		{
			if(it < max_heap.top())
			{
				max_heap.pop();
				max_heap.push(it);
			}
		}
	}

	for(int i = 0; i < k; i++)
	{
		res.push_back(max_heap.top());
		max_heap.pop();
	}
	return res;
}


// 分层打印BT
void BFSBST(TreeNode* root)
{
	queue<TReeNode*> Q;
	Q.push(root);
	while(!Q.empty())
	{
		int s = Q.size(); // 一进来就算一个size
		for(int i = 0; i < s; i++)
		{
			TreeNode* cur = Q.pop();
			Q.pop();
			cout<<cur->val<<endl;
			if(cur->left != nullptr)
			{
				Q.push(cur->left);
			}
			if(cur->right != nullptr)
			{
				Q.push(cur->right);
			}
		}
	}
}


bool isCompleteTree(TreeNode* root)
{
	// 找到第一个nullptr后， 后面不可以找到其他的非nullptr
	queue<TreeNode*> Q;
	Q.push(root);
	bool flag = true;
	int count = 1;

	while(!Q.empty())
	{
		TreeNode* cur = Q.top();
		Q.pop();
		if(cur->left == nullptr)
		{
			if(count == 1)
			{
				count = 0;
			}
		}else
		{
			if(count == 0)
			{
				return false;
			}else
			{
				Q.push(cur->left);
			}
		}

		if(cur->right == nullptr)
		{
			if(count == 1)
			{
				count = 0;
			}
		}else
		{
			if(count == 0)
			{
				return false;
			}else
			{
				Q.push(cur->left);
			}
		}
	}
	return true;
}


// Dijistra
class Node
{
	int cost;
	bool expanded;
	string name;
	vector<Node*> sucessors;
}

// 											BFS2,Dijkstra思想
// 								kth smallest in 2d sorted Matrix
struct Node
{
	int val;
	int row;
	int col;
}
struct compare
{
	bool operator()(const Node& node1, const Node& node2)
	{
		return node1.val > node2.val;
	}
}
int kthSmallest2D(vector<vector<int>>& matrix, int k)
{
	// expand k次， generate 2k 次
	if( k < 0 || matrix.size() == 0 || matrix[0].size()==0)
	{
		return INT_MAX;
	}
	int row = matrix.size();
	int col = matrix[0].size();

	// step1: 建立一个最小堆,
	priority_queue<Node, vector<Node>, compare> min_heap;
	// 记录某一个元素是否被访问过
	// 20 与 15 都会访问25
	vector<vector<bool>> visited(row,vector<int>(col, false));
	// 初始化最小堆
	min_heap.push({matrix[0][0], 0, 0});
	int result = 0;

	// step2: 对最小堆做 k -1 次操作后， 堆顶就是第k小数字，k = 1 ... n
	for(int i = 0; i < k - 1; i++)
	{
		// 取出堆顶元素，当前最小值
		Node cur = min_heap.top();
		int r = cur.row;
		int c = cur.col;
		min_heap.pop();// logn

		// insert two neibourhood: 2log(k)
		// 插入堆顶的下方点
		if(r + 1 < row - 1 && visited[r + 1][c] == false)
		{
			min_heap.push({matrix[r + 1][c], r + 1, c});
			visited[r+1][c] = true;
		}
		// 插入堆顶右方点
		if(c + 1 < col - 1 && visited[r][c + 1] == false)
		{
			min_heap.push({matrix[r][c + 1], r, c + 1});
			visited[r][c + 1] = true;
		}
		result = cur.val; // 或者这里弹出第K次的时候，得到的就是结果
	}

	// 堆顶即为第K小
	return min_heap.top();
}
// Time: there are k element, 
//		for each element, we need to pop top element for expansion, logk
//		for expansion, push 2 neighbours to heap, 2logk
// total is time complexity is O(3klogk) = O(klogk)
// space O(2k) = O(k)

// 10, 20, 30, 40
// 15, 25, 35, 45
// 24, 29, 37, 48
// 32, 33, 39, 50

// 1, 1, 0, 0
// 1, 1, 0, 0
// 1, 0, 0, 0
// 0, 0, 0, 0

// k = 4
// i = 2
//min heap
//				24
//			  25  30  
//			
//
//res = 20
// return min_heap.top()













