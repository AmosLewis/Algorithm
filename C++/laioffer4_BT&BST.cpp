class TreeNode{
	int val;
	TreeNode* left;
	TreNode* right;
	TreeNode():left(nullptr), right(nullptr){}
}

int getHeight(TreeNode* root)
{
	// Time O(n)
	// Space O(n), O(height)可能向linkedlist,最坏情况下O(height) = O(n)
	if(root == nullptr)
	{
		return 0;
	}
	int height_left = getHeight(root->left) + 1;
	int height_right = getHeight(root->right) + 1;
	return max(height_left, height_right);
}

bool isBalanced(TreeNode* root)
{
	// Time O(nlogn)
	// Space O(n), O(height)可能向linkedlist,最坏情况下O(height) = O(n)
	if(root == nullptr)
	{
		return true;
	}
	int height_left = getHeight(root->left) + 1; // O(n/2) n= number of subnode
	int height_right = getHeight(root->right) + 1; // O(n/2) n= number of subnode
	if(abs(height_left - height_right) > 1)
	{
		return false;
	}else
	{
		return isBalanced(root->left) && isBalanced(root->right);
	}
}

//							isBalanced(root) 
//							n/2 + n/2									n
//		isBalanced(root->left)		isBalanced(root->right)
//		n/4+n/4						n/4 + n/4 							n
//	ll				rr 			rl					rr
// n/8+n/8			n/8+n/8		n/8+n/8				n/8+n/8				n
// 每层都是n
// height = logn
// Time O(nlogn)

// isBalanced 更好的方法
class Solution {
public:
    bool isBalanced(TreeNode* root) {
        if(!root) return true;
        
        // 设置一个全局变量，在递归的过程中设置它
        bool balanced = true;
        
        int height_all = height(root, &balanced);
        
        return balanced;
    }
    
    int height(TreeNode* node, bool* balanced)
    {
        if(!node) return 0;
        // 递归求高度
        int height_left = height(node->left, balanced);
        int height_right = height(node->right, balanced);
        if(abs(height_left - height_right) > 1)
        {
            // 在递归的过程中设置全局变量
            *balanced = false;
            // 一旦发现不满足条件， 立马返回
            return -1;
        }
        // 高度定义 左右子树最大值+1
        return max(height_left, height_right) + 1;
    }
    
};


bool isSymmetrical(TreeNode* root)
{
	if(root == nullptr)
	{
		return true;
	}
	return isSymmetrical(root->left, root->right);
}
bool isSymmetrical(TreeNode* node1, TreeNode* node2)
{
	// 这三个Base case 就是O(3) = O(1)
	if(node1 == nullptr && node2 == nullptr)
	{
		return true;
	}else if(node1 == nullptr || node2 == nullptr)
	{
		return false;
	}else if(node1->val != node2->val)// if(node1 != nullptr && node2 != nullptr)
	{
		return false;
	}

	// 每个node 做一次&&，O(1),n个node就是O(n)
	return isSymmetrical(node1->left, node2->right) && 
		   isSymmetrical(node1->right, node2->left);
}


bool isIdentical(TreeNode* node1, TreeNode* node2)
{
	if(node1 == nullptr && node2 == nullptr)
	{
		return true;
	}else if(node1 == nullptr || node2 == nullptr)
	{
		return false;
	}else if(node1->val != node2->val)// if(node1 != nullptr && node2 != nullptr)
	{
		return false;
	}

	return (isIdentical(node1->left, node2->left) && isIdentical(node1->right, node2->right)
		|| (isIdentical(node1->left, node2->right) && isIdentical(node1->right, node2->left));
}


// is BST
bool isBST(TreeNode* root)
{
	return isBSTHelper(root, INT_MIN, INT_MAX)
}
// 									 INT_MIN     INT_MAX
bool isBSTHelper(TreeNode* root, int min, int max)
{
	if(root == nullptr) return true;
	if(root->val <= min ||root->val >= max) return false;

	return isBSTHelper(root->left, min, root->val) &&
		   isBSTHelper(root->right, root->val, max);
}


// print BST key in range[l1, k2]
// 这个方法遍历了所有点，没有用到BST的性质
void inorder(TreeNode* root, int k1, int k2)
{
	// O(n)
	if(root == nullptr) return;
	inorder(root->left, k1, k2);
	if(root->val >= k1 && root->val <= k2)
	{
		cout<<root->val<<" ";
	}
	inorder(root->right, k1, k2);
	return;
}

// void inorder2(TreeNode* root, int k1, int k2)
// {
// 	// O(k2-k1)
// 	// 这个方法是错的， 比如[9 14],对于15，左边有11 满足条件，但是这里直接返回了
// 	if(root == nullptr) 
// 	{
// 		return;
// 	}
// 	if(root->val < k1)
// 	{
// 		return;
// 	}
// 	if(root->val > k2)
// 	{
// 		return;
// 	}
// 	inorder(root->left, k1, k2);
// 	cout<<root->val<<" ";
// 	inorder(root->right, k2, k2);
// 	return;
// }
// //					 10 					[9,14]
// // 				5		  15
// // 			  2   6	    11   20
// //				   7	    18  25
// //					8	   17

void inorder3(TreeNode* root, int k1, int k2)
{
	// 老师给的方法
	// O(k2-k1)
	if(root == nullptr) 
	{
		return;
	}
	// 只要往左边走，就要check
	if(root->val > k1)
	{
		inorder3(root->left, k1, k2);
	}

	if(root->val >= k1 && root->val <= k2)
	{
		cout<<root->val << " ";
	}

	// 只要往右边走，就要check
	if(root->val < k2)
	{
		inorder3(root->right, k1, k2);
	}
}


// Traverse BST find target
// TreeNode* traverseBST(TreeNode* root, int target)
// {
// 	while(!root)
// 	{
// 		if(target < root->val)
// 		{
// 			root = root->left;
// 		}else if(target > root->val)
// 		{
// 			root = root->right;
// 		}else
// 		{
// 			return root;
// 		}
// 	}
// 	// root == nullptr
// 	return root;
// }
TreeNode* traverseBST(TreeNode* root, int target)
{
	while(!root || root->val != target) // terminate condition
	{
		if(target < root->val)
		{
			root = root->left;
		}else if(target > root->val)
		{
			root = root->right;
		}
	}
	// root == nullptr || root->val == target
	return root;
}

// TreeNode* traverseBST(TreeNode* root, int target)
// {
// 	if(root == nullptr)
// 	{
// 		return nullptr;
// 	}else if(root->val < target)
// 	{
// 		return traverseBST(root->right, target)
// 	}else if(root->val > target)
// 	{
// 		return traverseBST(root->left, target)
// 	}else 
// 	{
// 		return root;
// 	}
// 	return nullptr;
// }

TreeNode* traverseBST(TreeNode* root, int target)
{
	if(root == nullptr || root->val == target)
	{
		return root;
	}
	// tail recursion
	if(root->val < target)
	{
		return traverseBST(root->right, target)
	}
	if(root->val > target)
	{
		return traverseBST(root->left, target)
	}
}

// recusrion I:  最简洁写法，但是不建议写，因为要多次重复写
// 但是这个方法又很重要，因为强化练习会有很多题这个样子
// insertBST 只会在叶子节点插入新值，不会改变中间结构
TreNode* insertBST(TreeNode* root, int target)
{
	if(root == nullptr)
	{
		return new TreeNode(target);
	}

	// 递归向子树中插入target 
	if(root->key < target)
	{
		// 常见错误， 漏写root->right,白忙活
		// 这个方法的劣质是会有冗余，这个方法始终要重复写
		root->right = insertBST(root->right, target);
	}else if(target < root->key)
	{
		// 常见错误，漏写root—>left, 白忙活
		root->left = insertBST(root->left, target);
	}

	// 返回没有改变的根节点，
	return root;
}
// 例子
// 					6				5
//			    4	    9
//			  2   1	   7  11
// 					5
// 			 insert(6, 5)			return 6
// 6->left = insert(4, 5) 			return 4
// 4->right = insert(1, 5)			return 1	
// 1-right = nullptr return new TreeNode(5)		

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

































