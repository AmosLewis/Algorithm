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
