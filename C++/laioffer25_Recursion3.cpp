//laioffer25_Recursion3.cpp

// Q1 Tree + Recursion 第一类问题 人行问题
// Q1.1 O(nlogn) is balanced Tree + get height
// Q1.2 O(n) is balanced Tree + get height
bool isBalanced(TreeNode* root)
{
	int height = getHeight(root)
	return height == -1 ? false : true;
}
int getHeight(TreeNode* root)
{
	if(root == nullptr)
	{
		return 0;
	}
	int left = getHeight(root->left);
	int right = getHeight(root->right);

	if(left == -1 || right == -1 ||
		abs(left - right) > 1)
	{
		return -1;
	}
	return max(left, right) + 1;
}


// Q1.3 maxsum from one leaf node to another
// 1. ask from child: max of path [left_sum, left_leaf] 
//					  max of path[right, right_leaf] 
// 2. current layer:
// 				if(left exist && right exist)
//					update global_max
//					
// 3. return 
//   if(left exist && right exist)
//   return max(max_right + max_left) + root->val
//   if one of them not exit, return another node + root->val

int maxPathLeaf(TreeNode* root)
{
	if(root == nullptr)
	{
		return INT_MIN;
	}

	int global_max = INT_MIN;
	helper(root, global_max);
	return global_max;
}
int helper(TreeNode* root, int& global_max)
{
	if(root == nullptr)
	{
		return 0;
	}
	int max_left = helper(root->left, global_max);
	int max_right = helper(root->right, global_max);

	if(root->left && root->right)
	{
		global_max = max(global_max, max_left + max_right + root->val);// 人形path
		return max(max_left, max_right) + root->val;// 直上直下path
	}

	return root->left == nullptr ? (max_right + root->val) : (max_left + root->val);
}
// time: O(n)
// Space: O(logn) balanced tree
// 		O(n) worst case



// Q1.4 人行路径
// max path sum for any node in BT
// 如果从子节点接收到的是负数，就传递 自己
// 如果从子节点接收到的是正数，就传递 自己 + 子
int maxPathSum(TreeNode* root)
{
	if(root == nullptr)
	{
		return INT_MIN;
	}

	int global_max = INT_MIN;
	helper(root, global_max);
	return global_max;
}
int helper(TreeNode* root, int& global_max)
{
	if(root == nullptr)
	{
		return 0;
	}

	int max_left = helper(root->left, global_max);
	int max_right = helper(root->right, global_max);

	max_left = max_left < 0 ? 0 : max_left;
	max_right = max_right < 0 ? 0 : max_right;
	global_max = max(global, max_left + max_right + root->val);

	return max(max_left, max_right) + root->val;
}



// Q2 Tree + Recursion 第二类问题 直上直下的问题
// path prefix 问题，位置一个vector of path prefix, 可以做任何事

// Q2.1 找从root到叶子的最大路径和
// 就是preorder
void helper(TreeNode* node, int& prefix, int& global_max)
{
	if(node == nullptr)
	{
		return;
	}
	prefix += node->val;
	if(!root->left && !root->right)
	{
		global_max = max(global_max, prefix);
		return;
	}
	helper(node->left, prefix, global_max);
	helper(node->right, prefix, global_max);
}


// Q2.2 树中是否存在一段路径和为target
// 法1 O(n^2),到每个点回头看n次
void pathSumTarget(TreeNode* node, vector<int>& prefix, int target, bool& flag)
{
	if(!node)
	{
		return;
	}
	prefix.push_back(node->val);
	// 以最后一个点开始，向前面累加得到所有结果与target 比较
	if(helper(prefix, target))
	{
		flag = true;
	}
	pathSumTarget(node->left, prefix, target);
	pathSumTarget(node->right, prefix, target);
	prefix.pop_back();
}
bool helper(vector<int>& prefix, int target) // O(n)
{
	int n = prefix.size();
	int temp = 0;
	for(int i = n - 1; i >=0; i++)
	{
		temp += prefix[i];
		if(temp == target)
		{
			return true;
		}
	}
	return false;
}
// 有n个TreeNode点，每个点都向前O(n),总的O(n^2) 
// follow up : 如何优化时间 成O(n)

// 法2 recursion + path prefix sum
// 					而path prefix sum可以用DP的思想不断回头看+前面一个值来计算
// 用记录一个prefix_sum[],
// 对于prefix_sum用two_sum的思路解决，即全部元素hash_set
// find if (cur_prefix_sum - target) in hash_set
//		if exist, than find target return true;
bool pathAnySumTarget(TreeNode* root, int target)
{
	if(!root)
	{
		return false;
	}
	unordered_set<int> prefix_set;
	int prefix_sum;
	pathAnySumTarget(root, target, prefix_set, prefix_sum);
}
bool pathAnySumTarget(TreeNode* root, int target, unordered_set<int>& prefix_set, int prefix_sum)
{
	if(!root)
	{
		return false;
	}
	cur_prefix_sum = prefix_sum + root->val;
	if(prefix_set.count(cur_prefix_sum - target))
	{
		return true;
	}
	prefix_set.insert(cur_prefix_sum);
	bool left_flag = pathAnySumTarget(root->left, target, cur_prefix_sum);
	bool right_flag = pathAnySumTarget(root->right, target, cur_prefix_sum);
	//prefix_sum -= root->val;
	prefix_set.erase(cur_prefix_sum);
	return  left_flag || right_flag;
}



// 上面这题的变种，上面问是否有target，
// 这题问有[多少个]这种[路径和]为target的
// leetcode 437 path Sum 3
// 同样还是two_sum的思想 求target，转换为找sum-target是否出现过
// 不同之处在于上面用hash_set， 这里用hash_map记录每个set中的前缀树出现了几次
// 出现了几次就有几条路径
int pathSumCount(TreeNode* root, int sum) {
    if(!root)
    {
        return 0;
    }
    int total = 0;
    // 不包含当前节点，所有之前节点prefix_sum 初始化为0
    // [prefix_sum, nums of prefix_sum] // 只用set这个例子过不了[0, 1, 1] 
    // 不同的prefix可能包含的路径和是相同的，所以就有了多个结果
    unordered_map<int, int> prefix_map; 
    prefix_map[0] = 1;
    helper(root, sum, prefix_map, 0, total);
    return total;
}
void helper(TreeNode* root, int target, 
            unordered_map<int, int>& prefix_map, // 不包含当前节点，所有之前节点prefix_sum,及对应出现次数
            int prefix_sum, // 所有之前节点的和，初始化为0
            int& total)
{
    if(!root)
    {
        return;
    }
    int curSum = prefix_sum + root->val; // 包含当前节点的prefix_sum
    if(prefix_map.count(curSum - target))
    {
        total += prefix_map[curSum - target];
    }
    prefix_map[curSum]++;
    
    helper(root->left, target, prefix_map, curSum, total);
    helper(root->right, target, prefix_map, curSum, total); 
    
    prefix_map[curSum]--;
}




// q2.3 max path sum binary tree  直上直下的
// sol1 O(n^2) 保存一个array，每到一个位置往会一直看

// sol2 O(n) DP 重点
// 思想 max sum of unsorted subarray, path prefix sum问题
// 记录一个之前的prefix的贡献，贡献为正，加上当前节点
// 							贡献为负，改变为当前节点
int maxPathSum(TreeNode* root) {
    if(!root)
    {
        return INT_MIN;
    }
    int global_max = INT_MIN;
    helper(root, global_max, 0);
    return global_max;
}
void helper(TreeNode* root, int& global_max, int prefix_sum)
{
    if(!root)
    {
        return;
    }
    if(prefix_sum < 0)
    {
        prefix_sum = root->val;
    }else
    {
        prefix_sum += root->val;
    }
    global_max = max(prefix_sum, global_max);
    helper(root->left, global_max, prefix_sum);
    helper(root->right, global_max, prefix_sum);
}
// 时间复杂度 O(n)
// Space O(n) 递归




// sol3 DP 从下往上建max sub array sum
// 左边传一个，右边传一个，谁大取谁，负数舍弃变为0
void helper(TreeNode* root, int& global_max)
{
	if(!root)
	{
		return 0;
	}

	int left_max = helper(root->left, global_max); // 返回包含root->left, 最大的sum
	int right_max = helper(root->left, global_max);

	int temp = max(0, max(left_max, right_max));
	global_max = max(global_max, temp + root->val);

	return temp + root->val;
}


// 3 Tree Serialization Problem

// Q3.1 一个tree inorder 放入双向链表
// linkedlist难点： 1. 永远不要失去头, 找到谁是头， 最左边的new_head
//				   2. 要存储上一轮的node 
class Node
{
	int val;
	Node* left;
	Node* right;
}
int BinaryTree2DoubleLinkedList(TreeNode* root)
{
	Node** head;
	static Node* pre = nullptr;

	helper(root, pre, head);

}
void helper(TreeNode* root, Node* pre, Node** head)
{
	if(!root)
	{
		return;
	}
	helper(root->left, pre, head);

	if(pre == nullptr)
	{
		*head = root;
	}else
	{
		pre->right = root;
		root->left = pre; 
	}
	pre = root;
	helper(root->left, pre, head);
}



// 4 Reconstruct Tree


















