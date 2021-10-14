// laioffer5_heap&GS.cpp


// K smallest elements in unsorted array
// 法1: offline算法
vector<int> kSmallest(vector<int>& nums, int k)
{
	// 维持一个nums大的最小堆,很耗空间
	// 遍历一次数组，往最小堆里面插入所有数据
	vector<int> results;
	if(nums.size() == 0 || nums.size() < k || k == 0)
	{
		return results;
	}
	priority_queue<int, vector<int>, greater<int>> minQueue;
	for(const auto& it : nums)// Time: O(nlogn) Space: O(n)
	{
		minQueue.push(it);
	}
	for(int i = 0; i < k; i++) // Time: O(klogn) Space: O(k)
	{
		results.push_back(minQueue.top());
		minQueue.pop()；// O(logn)
	}
	return results;
}
// Time O(nlogn)
// Space O(n)

// 法2：Max heap, online 算法
vector<int> kSmallest(vector<int>& nums, int k)
{
	// 维持一个K大的最大堆
	// 遍历一次数组，往最大堆里面插入K个数据
	vector<int> results;
	if(nums.size() == 0 || nums.size() < k || k == 0)
	{
		return results;
	}
	priority_queue<int> maxQueue;
	for(const auto& it : nums)// Time: O(nlogk) Space: O(k)
	{
		if(maxQueue.size() < k)
		{
			maxQueue.push_back(it);
		}else if(it < maxQueue.top())
		{
			maxQueue.pop();
			maxQueue.push(it);
		}
	}
	for(int i = 0; i < k; i++) // Time: O(klogk) Space: O(k)
	{
		results.push_back(maxQueue.top());
		minQueue.pop()
	}
	return results;
}
//Time: O(nlogk)
//Space: O(k)


// 法3 quick sort partition
// 最坏的情况：O(n^2)
// 即每次都取最大的数，n + n-1 + n-2 +...+1 = n(1+n)/2
// average: O(n)
// 每次减少一半：n + n/2 + n/4 + .... = 2n 
vector<int> kSmallest(vector<int>& nums, int k)
{
	vector<int> result;
	KSmallestQuickSort(0, nums.size() - 1, k, nums, result);

	return result;
}
void KSmallestQuickSort(int start, int end, int k, vector<int>& nums, vector<int>& result)
{
	if((end - start + 1) == k)
	{
		for(int i = start; i <= end; i++)
		{
			result.push_back(nums[i]);
		}
	}

	int pivot = start + (end - start) / 2;
	int target = nums[pivot];
	int left = start, right = end;

	while(left <= right)
	{
		while(left <= right && nums[left] < target) left++;
		while(left <= right && nums[right] > target]) right--;
		if(left <= right)
		{
			swap(nums[left], nums[right]);
			left++;
			right--;
		}
	}
	// start       right left      end
	if(k <= right)
	{
		KSmallestQuickSort(start, right, k, nums, result);
	}
	if(k >= left)
	{
		// 把前一半的数放入结果中保存
		for(int i = start; i < right; i++)
		{
			result.push_back(nums[i]);
		}
		// 去右边去找剩下的 k - left 个数
		KSmallestQuickSort(left, right, k - left, nums, result);
	}
}






// 												最小堆的实现
heapify(vector<int>& A)
{
	// O(n)
	// node index [0, end]
	// getLastNodeIndex 
	int end = A.size() / 2 - 1;
	// 对每一个非叶子节点，做一次heapify down
	for(int i = end; i >= 0; i++)
	{
		heapify_down(A, i);
	}
}

void heapify_down(vector<int>& A, int index)
{
	// 在minheap.pop时候也要用，就是O(logn),顶上元素拿出来，
	// 用最后一个元素替代，然后一路向下迭代，并不需要完整的heapfiy_down
	// 完整的heapify_down,用于建立最小堆，这种建立堆的方法快， 是O(n)的
	int index_smallest = index;
	int index_left = 2 * i + 1;
	int index_right = 2 * i + 2;

	// 找到3个数字中最小的元素的index
	if(index_left < A.size() && A[index_left] < A[index])
	{
		index_smallest = index_left;
	}
	if(index_right < A.size() && A[index_right] < A[index_smallest])
	{
		index_smallest = index_right;
	}

	// 不满足堆的条件， 若满足 则 index == index_smallest
	if(index != index_smallest)
	{
		swap(A[index], A[index_smallest]);
		heapify_down(A, index_smallest);
	}
}
// Time
// full binary tree : height = k, node = 2^k - 1
// 					2
//			3				4
// 	  5			 6		7		8
// s 表示向下比较的次数，
// 倒数第一层是叶子,不用看,有2^(k-1)个元素，向下比较0次，
// 对于最后第2层，有2^(k-2)个元素，向下比较1次，
// 对于最后第3层，有2^(k-3)个元素，向下比较2次
// 对于最后第4层，有2^(k-4)个元素，向下比较3次
// ...
// 对于最后第k层，有2^(k-k)个元素，向下比较k-1次
// 
// s  = 			1*2^(k-2) + 2*2^(k-3) + 3*2^(k-4) + ... + (k-2)*2^1 + (k-1)*2^0
// 2s = 1*2^(k-1) + 2*2^(k-2) + 3*2^(k-3) +     ...    ... + (k-1)*2^1
// s  = 2s - s = 2^(k-1) + 2^(k - 2) + 2^1 - (k-1)*2^0
// s = 2^(k-1) + 2^(k-2) + ... + 2^1 - (k-1)
//   = 2^(k-1) + 2^(k-2) + ... + 2^1 + 2^0 - k
//   = a1 *(1-q^n) / (1 - q)
//	 = 1 * (1-2^k) / (1 - 2) - k
//	 = O(2^k) = O(n)
// 直觉上，k巨深， 一半的元素O(1/2*(2^k - 1)) = O(n/2) = O(n)只要向下比较一次

// index 最后一行的最后一个元素
void heapify_up(vector<int>& A, int index)
{
	// index 表示所有
	// push_back 元素时候会用到，vector尾部插入，得到size-1， 就是index
	// 这个方法更慢一些 是 O(nlogn)
	int index_parent = (index-1)/2;
	if(index_parent != 0 && A[index] < A[index_parent])
	{
		swap(A[index], A[index_parent]);
		heapify_up(A, index_parent);
	}
}
// 自顶向下看，
// 第0层，有一个元素放进来，向上比0次
// 第1层，有2^1个元素放进来，向上比1次
// 第2层，有2^2个元素放进来，向上比2次
// ...
// 第k-1层，有2^(k-1)个元素放进来，向上比(k-1)次
// s = 0 + 1*2^1 + 2*2^2 + 3*2^3 + ... (k-1)*2^(k-1)
//2s = 0 + 		   1*2^1 + 2*2^3 + ... (k-2)*2^(k-1) + (k-1)*2^k
// s = 0 -   2^1 - 2^2   - 2^3	 - ... -2^(k-1) + (k-1)*2^k
// s = 0 -   2^1 - 2^2   - 2^3	 - ... -2^(k-1) - 2^k + k*2^k
// 当k特别大 前面的项都不用看，因为常数增长没有指数快， 
// 指数增长后面一项远远大于前面几项和
// 所以 s 约等于
// O(k*2^k) = O(logn * n)= O(nlogn)



// 												BFS

// 层次遍历二叉树
class TreeNode{
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode():left(nullptr), right(nullptr){}
}

vector<int> BFSBinaryTree(TreeNode* root)
{
	vector<int> result;
	queue<TreeNode*> q;
	q.push(root);

	while(!q.empty())
	{
		// 这句话很关键，只有这样，才能保证这一层的所有节点
		// 在下面这个for循环中都被遍历到并弹出
		int size = q.size();
		for(int i = 0; i < size; i++)
		{
			TreeNode *node = q.top();
			q.pop();
			result.push_back(node->val);
			if(q->left != nullptr)
			{
				q.push(q->left);
			}
			if(q->right != nullptr)
			{
				q.push(q->right);
			}
		}

	}
	return result;
}


// 								isBipatite
class GraphNode
{
	int val;
	char flag;
	vector<GraphNode*> sucessor;
}

bool isBipatite(vector<GraphNode*>& graph)
{
	// BFS graph, init the first node as 'v'
	// set successor as 'u'
	// set sucessor's sucessor as 'v'
	// if find conflict,return false
	for(auto & it:graph)
	{
		it->flag = 'a'; // this node has not set to u/v
	}

	queue<GraphNode*> q;
	graph[0]->flag = 'u';
	q.push(graph[0]);
	char help = 'u' + 'v';

	while(!q.empty())
	{
		GraphNode* curnode = q.top();
		q.pop();

		for(auto& it : curnode->sucessor)
		{
			if(it->flag == 'a')// 子节点没有设置过，设置
			{
				it->flag = help - curnode->flag;
			}else if(help - curnode->flag != it->flag) // 已经设置过两次设置的冲突
			{
				return false;
			}
			q.push(it);
		}
	}
	return true;
}


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




















