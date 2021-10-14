//laioffer26_JQ4.cpp

// q1.1 reverse linkedlist
Node* reverseLinkedList(Node* head)
{
	if(!head || !head->next)
	{
		return head;
	}

	Node* next = head->next;
	Node* new_read = reverseLinkedList(head->next);

	next->next = head;
	head->next = nullptr;

	return new_head;
}


// q1.2 reverse linkedlist pair by pair
Node* reverseLinkedListPair(Node* head)
{
	if(!head || !head->next)
	{
		return head;
	}

	Node* new_head = head->next;
	Node* new_next_head = reverseLinkedListPair(head->next->next);

	new_head->next = head;
	head->next =new_next_head;

	return new_head;
}

// Q1.3 Reverse Binary Tree upside down
TreeNode* reverseBinaryTree(TreeNode* root)
{
	if(!root || !root->left)
	{
		return root;
	}

	TreeNode* new_root = reverseBinaryTree(root->left);
	root->left->right = root;
	root->left->left = root->right;
	root->left = nullptr;
	root->right = nullptr;

	return new_root;
}


// Q2.1 find subsuet [a,b,c]
vector<string> findSubset(string& str)
{
	vector<string>& solution;
	string& temp;
	help(str, 0, temp, solution);
}
void help(string& str, int id, string& temp, vector<string>& solution)
{
	if(id == str.size())
	{
		solution.push_back(temp);
		return;
	}

	temp.append(str[id]);
	help(str, id + 1, temp, solution);
	temp.pop_back();
	hep(str, id + 1, temp, solution);
}

// q2.1b 是否可以分成两部分和相同
// DFS方法超时, 有DP的方法
bool canPartition(vector<int>& nums) {
    if(nums.empty())
    {
        return true;
    }
    int sum = 0;
    for(auto it:nums) sum += it;
    float target = sum / 2.0;
    bool flag = false;
    float temp = 0;
    help(nums, 0, temp, target, flag);
    return flag;
}
void help(vector<int>& nums, int id, float& temp, float target, bool& flag)
{
    if(temp == target)
    {
        flag = true;
        return;
    }
    if(id == nums.size())
    {
        return;
    }
    temp += nums[id];
    help(nums, id + 1, temp, target, flag);
    temp -= nums[id];
    help(nums, id + 1, temp, target, flag);
}


// q2.1c
// 无重复元素的array
// 找所有combination of array, subset size == k
// O(2^n)
vector<vector<int>> subsetK(vector<int>& A, int k)
{
	vector<vector<int>> solution;
	vector<int> temp;
	help(A, k, 0, temp, solution);
}
void help(const vector<int>& A, int k, int id, 
	vector<int>& temp, vector<int>& soltuion)
{
	if(temp.size() == k)
	{
		solution.push_back(temp);
		return;
	}
	if(id == A.size())
	{
		return;
	}
	temp += A[id];
	help(A, k, id + 1, temp, solution);
	temp == A[id];
	help(A, k, id + 1, temp, solution);
}


// q2.1d
// 有重复元素的array
// 先sort一下
vector<vector<int>> subsetDup(vector<int>& A)
{
	vector<vector<int>> solution;
	vector<int> temp;
	sort(A.begin(), A.end());
	help(A, 0, temp, solution);
}
void help(const vector<int>& A, int id, 
	vector<int>& temp, vector<int>& soltuion)
{
	if(id == A.size())
	{
		return;
	}
	temp += A[id];
	help(A, id + 1, temp, solution);
	temp == A[id];
	help(A, id + 1, temp, solution);

	// 只要开始不加，遇到所有重复都不加， 这3行是这题的关键
	while(id < A.size() - 1 && A[id] == A[id+1])
	{
		id++;
	}
}

// q2.1 e
// 有重复元素的array 取k个
// 先sort一下
vector<vector<int>> subsetDupK(vector<int>& A, int k)
{
	vector<vector<int>> solution;
	vector<int> temp;
	sort(A.begin(), A.end());
	help(A, 0, temp, solution);
}
void help(const vector<int>& A, int k, int id, 
	vector<int>& temp, vector<int>& soltuion)
{
	if(temp.size() == k)
	{
		solution.push_back(temp);
		return;
	}
	if(id == A.size())
	{
		return;
	}
	temp += A[id];
	help(A, k, id + 1, temp, solution);
	temp == A[id];
	help(A, k, id + 1, temp, solution);

	// 只要开始不加，遇到所有重复都不加， 这3行是这题的关键
	while(id < A.size() - 1 && A[id] == A[id+1])
	{
		id++;
	}
}



// Q2.2a
// 无重复
// 							       [null]abc
// 0 			[a]bc               [b]ac            [c]ab
// 1	   A[b]c    A[c]b      B[a]c    B[c]a     C[a]b   C[b]a 
// 2       AB[c] 	AC[b]  	 BA[c] 		BC[a]  	  CA[b]   CB[a]
// 3	   ABC      ACB.     BAC.       BCA.      CAB.    CBA 
vector<string> stringPermutation(string& str)
{
	vector<string> solution;
	help(str, 0, solution);
	return solution;
}
void help(string& str, int id, vector<string>& solution)
{
	if(id == str.size())
	{
		solution.push_back(str);
		return;
	}
	for(int i = id; i < str.size(); i++)
	{
		swap(A, id, i);
		help(str, id + 1, solution);
		swap(A, id, i);
	}
}

// Q2.2b
// 有重复
vector<string> stringPermutation(string& str)
{
	vector<string> solution;
	sort(str.begin(), str.end());
	help(str, 0, solution);
	return solution;
}
void help(string& str, int id, vector<string>& solution)
{
	if(id == str.size())
	{
		solution.push_back(str);
		return;
	}
	for(int i = id; i < str.size(); i++)
	{
		swap(A, id, i);
		help(str, id + 1, solution);
		swap(A, id, i);
		// 这句是关键
		while(i < str.size() - 1 && str[i+1] == str[i])
		{
			i++;
		}
	}
}


// Q2.3a
// 99 cent
vector<vector<int>> FindCoin(vector<int> coins, const int sum)
{
	vector<vector<int>> solution;
	vector<int> temp;
	sort(coins.rbegin(), coins.rend()); // decending order
	help(coins, sum, 0, temp, solution);

	return solution;
}
void help(const vector<int>& coins, const int remain_sum, int id, 
			vector<int>& temp,
			vector<vector<int>>& solution)
{
	if(id == coins.size() - 1)
	{
		coins[id] = remain_sum;
		solution.push_back(temp);
		return;
	}

	for(int i = 0; i < remain_sum / coins[id]; i++)
	{
		temp[id] = i;
		help(coins, remain_sum - coins[id] * temp[id], id + 1, temp, solution);
	}
}



// 2.3b
// combinations of factor
vector<vector<int>> factorCombinations(int p)
{
	vector<int> factors;
	vector<int> count;
	vector<vector<int>> solution;
	help(p, 0, factors, count, solution);
}
void help(int remain_p, int id, const vector<int>& factors, 
			vector<int>& count, vector<vector<int>>& solution)
{
	if(id == factor.size())
	{
		solution.push_back(temp);
	}

	for(int i = 0; i < remain_p / factors[id]; i++)
	{
		counts[id] = i;
		help(remain_p / factors[id], id + 1, factors, count, solution);
	}
}



// 2.4a 
// permutaion ()()
vector<string> permutaionparenthisis(int n)
{
	string temp;
	vector<string> solution;
	help();
}
void help(int n, int l, int r, string& temp, vector<string>& solution)
{
	if(l == n && r == n)
	{
		solution.push_back(temp);
		return;
	}
	if(l < n)
	{
		temp.push_back('(');
		help(n, l + 1, r, temp, solution);
		temp.pop_back();
	}
	if(r < l)
	{
		temp.push_back(')');
		help(n, l, r + 1, temp, solution);
		temp.pop_back();
	}
}


// 2.4 b
// if{
//		}
//
void printParentheses(int n)
{
	string temp;
	vector<string> results;
	dfs(n, 0, 0, temp, results);
}
void dfs(int n, int l, int r, string& temp, vetor<string>& results)
{
	if(l == n && r == n)
	{
		results.push_back(format(temp));
		return;
	}

	if(l < n)
	{
		temp.push_back('(');
		dfs(n, l + 1, r, temp, results);
		temp.pop_back();
	}
	if(r < l)
	{
		temp.push_back(')');
		dfs(n, l, r + 1, temp, results);
	}
	return;
}
string format(string& str)
{
	string res;
	int num_Space=0;
	for(int i = 0; i < str.size(); i++)
	{
		if(str[i] == '(' )
		{
			addSpaces(res, num_Space);
			res += "if{ \n";
			num_Space +=2;
		}else// if(str[i] == ')')
		{
			num_Space -=2;
			addSpaces(res, num_Space);
			res += "} \n"
		}
	}
	return res;
}
void addSpaces(string res, int num_Space)
{
	while(num_Space--)
	{
		res = ' ' + res;
	}
}
// Time O(2^2n) 2n树的高度，n 括号的个数
// 二叉树，叶子节点2^2n个
// Space  O(2n) 2n树的高度






















