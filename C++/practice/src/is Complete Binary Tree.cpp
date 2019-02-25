// 									is complete Binary tree
bool isCompleteBinaryTree(TreeNode* root)
{
	// 用Queue确保每次只对一层遍历
	queue<TreeNode*> q;
	q.push(root);
	int count = 1; // 是否是第一次遇到空,第一次遇到空以后又遇到空，就返回false

	while(!q.empty())
	{
		TreeNode* cur = q.top();
		q.pop();

		if(cur->left)
		{
			q.push(cur->left);
		}else if(count == 1)
		{
			count--;
		}else
		{
			return false;
		}

		if(cur->right)
		{
			q.push(cur->right);
		}else if(count == 1)
		{
			count--;
		}else
		{
			return false;
		}
	}
}
//				10
//			8		9
//		  7	  6   5	  null
//	 null  4 3 2 1 null
