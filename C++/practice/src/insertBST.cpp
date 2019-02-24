// recusrion I:  最简洁写法
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
		// 这个方法的劣质是会有冗余，这个方法始终要做写操作
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
