//java9_BST2.cpp
//preorder inorder postorder


void preorder(TreeNode* root)
{
	if(!root)
	{
		return;
	}
	stack<TreeNode*> st;
	st.push(root);
	while(!st.empty())
	{
		TreeNode* cur = st.top();
		st.pop();
		cout<<cur->val<<endl;
		if(!cur->right)
		{
			st.push(cur->right);
		}
		if(!cur->left)
		{
			st.push(cur->left);
		}
	}
}


void inorder(TreeNode* root)
{
	stack<TreeNode*> st;
	st.push(root);
	TreeNode* helper = root;
	while(helper != nullptr || !st.empty())// 栈空可能意味着 不再有节点的左子树没有完成遍历，包括根也被遍历过了，但是右子树可能还有
	{
		if(helper != nullptr)
		{
			st.push(helper);
			helper = helper->left;
		}else
		{
			helper = st.top();
			cout<<helper->val<<endl;
			st.pop();
			helper = helper->right;
		}
	}
}


void postorder(TreeNode* root)
{
	if(!root)
	{
		return;
	}

	stack<TreeNode*> st;
	TreeNode* pre = nullptr; // pre是全局变量
	st.push(root);
	while(!st.empty())
	{
		TreeNode* cur = st.top();// cur是局部变量

		// going down left first
		if(pre == nullptr || pre->left = cur || pre->right = cur) // pre 在上面
		{
			if(cur->left)
			{
				st.push(cur->left);
			}else if(cur->right)
			{
				st.push(cur->right);
			}else
			{
				cout<<cur->val;
				st.pop();
			}
		}else if(pre == cur->left) // 从左边上来，pre在左下
		{
			if(cur->right)
			{
				st.push(cur->right);
			}else
			{
				cout<<cur->val<<endl;
				st.pop();
			}
		}else// pre == cur->right 从右边上来， pre 在右下
		{
			cout<<cur->val<<endl;
			st.pop();
		}
		
		pre = cur;// 这个极其容易忘， 要先写，循环结束后，pre指到cur
	}

}






