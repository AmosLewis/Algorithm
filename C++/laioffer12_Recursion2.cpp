//laioffer12_Recursion2.cpp

// a^b
// 1. 0 ^ 0 = 1, return -1
// 2. a = 0, b < 0: 0 as denominator, return -1
// 2. b < 0, return 
double pow(int a, int b)
{
	if(a == 0 && b <= 0)
	{
		return -1;
	}else if(b < 0)
	{
		return 1/(double)power(a, -b);
	}else{
		return (double)power(a, b);
	}
}
double power(int a, int b)
{
	if(b == 0)
	{
		return 1;
	}

	double result = power(a, b/2);
	if(b % 2 == 0)
	{
		return result * result;
	}else
	{
		return result * result * a;
	}
}



// 												2 Recursion with 1D 2D array
// 1D
// quicksort
// mergesort

// 2D array
// 2.1 K Queen
// if k = 8
//										  root
// level 0: Q0-Q7 	Q0-Q7	 Q0-Q7	 Q0-Q7	 Q0-Q7	 Q0-Q7	 Q0-Q7	 Q0-Q7
// levle 1: Q0...Q0
// time(k^k)

void kQueen(int k)
{
	vector<vector<int>> results;
	vector<int> visit(8, 0);// index means row, value means column
	kQueenHelp(visit, k, 0, results);
}
void kQueenHelp(vector<int>& visit, 
				int k, 
				int level, 
				vector<vector<int>>& results)
{
	// base case: the last row is down
	if(level == k)
	{
		results.push_back(visit);
		visit.clear();
		return;
	}

	// recurse rule: if position(i,j) valid, go to the next row(i+1, 0...7)
	for(int i = 0; i < k; i++)
	{
		// try put 0 .. 7 as valid result, then check weather it is valid
		visit[level] = i;
		if(isValid(visit))
		{
			kQueenHelp(visit, k, level + 1, results);
		}
	}
}
//	  0	1			2		3
//	i 
//	0 * 					*
//	1 *	visit[i]			visit[i]
//	2 *				col 	*
bool isValid(vector<int>& visit)
{
	int col = visit.back();
	for(int i = 0; i < visit.size() - 1; i++)
	{
		// 剔除行冲突 			剔除斜边冲突
		if(visit[i] == col || abs(col - visit[i]) == abs(visit.size() - i))
		{
			return false;
		}
	}
	return true;
}


// 2.2 print array in spiral order (N*N)
//	1	2	3	4	5
//  16	17	18	19	6
//	15	24	25	20	7
//	14	23	22	21	8
//	13	12	11	10	9
// size = size -2
// offset++
// start[r,c]
// r = r + offset
// c = c + offset 
// 4 * (print size - 1)
void spiral2DMatrix(int N)
{
	vector<vector<int>> A(N, vector<int>(N, 0));
	spiralPrint(A, 0, N, 1);
}

void spiralPrint(vector<vector<int>>& A, 
				int offset, 				// 新的起始位置距离 [0,0]有多远
				int size,					// 每一行元素的个数
				int counter)				// 全局变量，用于计数	
{
	if(size == 1)
	{
		A[offset][offset] = counter;
		// print A
	}else if(size == 0)
	{
		// print A
	}

	int N = A.size() - 1;
	// up row
	for(int i = 0; i < size - 1; i++)
	{
		A[0 + offset][i + offset] = counter++;
	}
	// right column
	for(int i = 0; i < size - 1;i++)
	{
		A[i + offset][N - offset] = counter++;
	}
	// buttoom
	for(int i = 0; i < size - 1;i++)
	{
		A[N-offset][N -offset - i] = counter++;
	}
	// left
	for(int i = 0; i < size - 1; i++)
	{
		A[N - offset - i][0 + offset] = counter++;
	}

	spiralPrint(A, offset+1, size - 2, counter);
}



// 											3 Recursion & Linkedlist
// 3.1 reverse a linkedlist
//			head	  subproblem	
//	    	node1 -> |node2 -> node3 -> ...... node* -> nodeN -> nullptr|
//			cur 	  next		
//			nullptr	  
// 子问题解决完后：					
//	    	node1    |node2 <- node3 <- ...... node* <- nodeN    		|
//			    		|
//			    	  nullptr
// 更改当前问题节点
//	    	node1 <- |node2 <- node3 <- ...... node* <- nodeN    		|
//			  | 		
//			nullptr	  nullptr	
//		 <- cur   <-  next
// base case
//	    	node1 -> |node2 -> node3 -> ...... node* -> nodeN -> nullptr|
//						     							head
class ListNode{
	int val;
	ListNode* next;
}
ListNode* reverseLinkedlist(ListNode* head)
{
	// base case
	// case1 全局输入就是空链表
	// case2 遍历到链表结尾， head 为最后一个非空node，此时自己反转自己就可以了
	// 		 反转完了就是一个子问题解决，变成了解决general的case
	if(head == nullptr || head->next == nullptr)
	{
		return head;
	}

	ListNode cur = head;
	ListNode next = head->next;

	// new_head是原来链表的尾部节点，不做任何改变从递归最底层一直向上传递
	ListNode* new_head = reverseLinkedlist(head->next);

	next->next = cur;
	cur->next = nullptr;

	return new_head;
}



// 3.2 Reverse a linkedlist pair by pair
// 
ListNode* reverseLinkedlistPairbyPair(ListNode* cur)
{
	//       cur
	// node1 node2 nullptr
	if(cur == nullptr || cur->next == nullptr)
	{
		return cur;
	}

	ListNode* nnext = reverseLinkedlistPairbyPair(cur->next->next);

	// node1 node2 | node3 <-node4
	// cur <-next 	 nnext
	// -------------->
	Linkedlist* next = cur->next;
	next->next = cur;
	cur->next = nnext;
	return next;
}


// Recursion & string
// 4.1 reverse a string
// abcd - bcda
void reverseString(string& str, int left, int right)
{
	if(left >= right)
	{
		return;
	}

	swap(str[left], str[right]);
	reverseString(str, left + 1, right - 1);
}


// 4.2 
// match string abbreviate
// s 1 1 d
// s ophistate d
// AbbreMatch




//									 5 Recursion & Tree
// 5.1  



// 5.1.4
class TreeNode{
	int val;
	TreeNode* left;
	TreeNode* right;
}
// lowest common ancestor in a tree
TreeNode* LowestAncestor(TreeNode* root, TreeNode* a, TreeNode* b)
{
	if(root == nullptr || root->val == a->val || root->val == b->val)
	{
		return root;
	}

	TreeNode* leftNode = LowestAncestor(root->left, a, b);
	TreeNode* rightNode = LowestAncestor(root->val, a, b);
	if(leftNode && rightNode)
	{
		return root;
	}
	// if(rightNode == nullptr)
	// {
	// 	return leftNode;
	// }else// if(leftNode == nullptr)
	// {
	// 	return rightNode;
	// }
	return leftNode == nullptr ? rightNode : leftNode;
}

TreeNode* LowestAncestorMain(TreeNode* root, TreeNode* a, TreeNode* b)
{
	TreeNode* solu = LowestAncestor(root, a, b);
	if(solu == nullptr)
	{
		return solu;
	}else if(solu != a && solu != b)
	{
		return c;
	}else // a b 直接隶属关系
	{
		// if(solu == a)
		// {
		// 	return LowestAncestor(solu, b, b) == nullptr ? nullptr : solu;
		// }
		// if(solu == b)
		// {
		// 	return LowestAncestor(solu, a, a) == nullptr ? nullptr : solu;
		// }
		return solu == a ? LowestAncestor(solu, b, b) : LowestAncestor(solu, a, a);
	}
}




































