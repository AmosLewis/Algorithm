//laioffer20_midterm.cpp

// 1. N queen
vector<vector<int>> Nqueen(int n)
{
	if(n < 0)
	{
		return {};
	}
	vector<vector<int>> results;
	vector<int> temp(0);
	nQueenSolve(n, 0, temp, results);
	return results;
}

void nQueenSolve(int n, int level, vector<int>& temp, vector<vector<int>>& results)
{
	if(level == n)
	{
		results.push_back(temp);
		return;
	}
	// 放所有可能的col
	for(int i = 0; i < n; i++)
	{
		if(isValid(temp, i))
		{
			temp.push_back(i);
			nQueenSolve(n, level + 1, temp, results);
		    temp.pop_back();
		}
	}
}
bool isValid(vector<int>& temp, int col)
{
	int row = temp.size();
	// 检查前面所有的行与当前行是否有冲突
	for(int i = 0; i < row; i++)
	{
		// 同列					斜边 col - col == row - row
		if(col = temp[i] || abs(col - temp[i]) == row - i)
		{
			return false;
		}
	}
	return true;
}
// recursion tree 有n层
// 每层 n 叉
// 第一层 n个分支，
// 第二层 n(n-1)个分支
// 第三层 n(n-1)(n-2)个分支
// ...
// 第n层 n(n-1)(n-2)...1个分支
// 时间复杂度与recursion tree node 数量有关，看最后一层的nodes数量就行了
// 即O(n!) 
// isValid O(n)
// 最终Time O(n*n!)

// 除了input output
// Auxiliary Space O(2n), 
// O(n):recursion tree 层数, callstack开销
// O(n):temp
// O(2n) = O(n)


// Q2 max path form leaf to leaf in tree
// 注意 node->val 可能是0

// tree 3 step
// step1. 问左右孩子要什么: 
//			max length form left to left's leaf node
// 			max length form right to right's leaf node
// step2. 当前层做点什么？
// 			通过当前节点得到的最大的path
//			if(左右都存在)
//			cur_sum = left_max + right_max + curnode->val
//			cursum > global_max, 更新global_max的值
// step3. 返回给parent什么？ 保证物理意义与1一样
// 				max(left_max, right_max) + cur->val if(左右都存在)
//				
// 				left_max + cur->val if(right 不存在)
//				right_max + cur-val if(left 不存在)
// 人字形的path，顶点的位置，分解成俩直上直下的path  
// 

int maxPathTree(TreeNode* root)
{
	if(root == nullptr) 
	{
		return INT_MIN;
	}
	int global_max = INT_MIN; 
	helper(root, global_max);
	return gloabl_max;
}
int helper(TreeNode* node, global_max)
{
	if(node == nullptr)
	{
		return 0;// 必须是0，最后一句用到了这个结果
	}
	int left_max = helper(node->left, global_max);
	int right_max = helper(node->right, global_max);

	// 只有当俩子树都存在，才可以做这个逻辑
	if(node->left && node->right) // 这个逻辑会忘
	{
		int cur_sum = left_max + right_max + node->val;
		global_max = max(cur_sum, global_max);
		return max(left_max, right_max) + node->val;
	}
	// if(node->left == nullptr)// 没有左子树
	// {
	// 	return right_max + node->val;
	// }else(node->right == nullptr)// 没有右子树
	// {
	// 	return left_max + node->val;
	// } 
	// return node->val;// 俩子树都不存在，该点是叶子
	return node->left == nullptr ? right_max+ node->val : left_max + node->val;
}

// n: number of node in the tree
// Time: O(n) 每个node花销O(1)
// Space: O(logn) balanced tree height, call stack
//		  O(n) worst case 




// Q3 fewest cur of partition of string is palindrome
// 左大段是sub problem 结果
// 右小段是保证一定是palindrome
// ababbbab
// a 			-> dp[1] = 0
// ab 			-> dp[2] = dp[1] + 1 = 1
// a | b
// aba
// dp[i] the number of cut that i elements need
int fewestCut(string& str)
{
	if(str.empty())
	{
		return -1;
	}
	vector<int> dp(str.size() + 1, 0);
	dp[0] = 0;
	dp[1] = 0;
	for(int i = 1; i < str.size(); i++)// O(n)
	{
		int global_min = INT_MAX;
		if(isPalindrome(str,0,i))// O(n)
		{
			dp[i] = 0;
		}else
		{
			for(int j = 0; j < i; j++)// O(n)
			{
				if(isPalindrome(str, j, i))
				{
					global_min = min(global_min, dp[j] + 1)
					dp[i] = global_min; 
				}
			}
		}
	}
	return dp[str.length()];
}
bool isPalindrome(const string& str, int l, int r)
{
	if(str.empty())
	{
		return true;
	}
	while(l <= r)
	{
		if(str[l] != str[r])
		{
			return false;
		}
		l++;
		r--;
	}
	return true;
}
// time O(n^3)
// space O(n)





// 4 print all possible if block give n

// 先写一下 ()() (()) n == 2
// 0 							  ""
// 1			        "("						)
// 2			"("			    ")"			 (	   )
// 3		(		")"	    "("      )
// 4.     (	  )   (   ")"  (  ")"  (   )
// (())
// ()()
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


































