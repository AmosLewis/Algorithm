// laioffer23_JQ2.cpp

// Q1 skeep list / graph copy problem
// Q1.1 deep copy linkedlist with random pointer
struct ListNode{
	int val;
	ListNode* next;
	ListNode* random;
	ListNode(int a): val(a), next(nullptr), random(nullptr){}
}

// 这题最重要的是有一个hash_table 记录每次新建的节点与当前节点的对应关系
// 后面遇到新的需要拷贝的点，看看时候已经被拷贝过，没有拷贝过就新建节点，拷贝过就直接指向
// Time(n)
ListNode* copyLinkedListWithRandom(ListNode* head)
{
	if(head == nullptr)
	{
		return head;
	}
	ListNode* new_head = new ListNode(head->val);
	ListNode* cur = new_head;
	unordered_map<ListNode*, ListNode*> my_map;
	while(head != nullptr)
	{
		if(head->next != nullptr)// next 存在， copy next
		{
			// head hasnot copied previously
			if(my_map.count(head->next) == 0)
			{
				my_map[head->next] = new ListNode(head->next->val);
			}
			cur->next = my_map[head->next];
		}
		if(head->random != nullptr) // random 存在， copy random
		{
			// random has not copied previously
			if(my_map.count(head->random) != nullptr)
			{
				my_map[head->random] = new ListNode(head->random->val);
			}
			cur->random = my_map[head->random];
		}
		cur = cur->next;
		head = head->next;
	}
	return new_head;
}


// Q1.2 copy a graph
// 两个方法 DFS BFS1 都要会
// 还是用一个hash_map 来maintain一个对应关系
class Node {
public:
    int val;
    vector<Node*> neighbors;

    Node() {}

    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

// BFS1
Node* cloneGraph(Node* node) {
    if(node == nullptr)
    {
        return node;
    } 
    queue<Node*> Q;
    Q.push(node);
    // 用一个hash_map建立原图与当前图之间的映射关系
    unordered_map<Node*, Node*> my_map;
    Node* new_node = new Node;
    new_node->val = node->val;
    my_map[node] = new_node;

    while(!Q.empty())
    {
        Node* cur = Q.front();
        Q.pop();

        for(const auto& it : cur->neighbors)
        {
            // 这个点还没有访问过， hash表中没有
            if(!my_map.count(it))
            {
                Q.push(it);
                Node* new_node = new Node;
                new_node->val = it->val;
                my_map[it] = new_node; 
            }
            my_map[cur]->neighbors.push_back(my_map[it]);
        }
    }
    return new_node;
}

// DFS1 
Node* cloneGraph(Node* node) {
    unordered_map<Node*, Node*> my_map; // [node,clone of node]
    return helper(node, my_map);
}

Node* helper(Node* node, unordered_map<Node*, Node*>& my_map)
{
    if(!node) 
    {
        return node;
    }
    // 已经克隆过，所以node及其所有邻居都已经都clone好了,放在my_map[node]里面
    if(my_map.count(node))
    {
        return my_map[node];//已经clone过了，直接已经clone好的返回
    }
    // 没有clone过，
    // step1 新建一个node, copy自己
    Node* new_node = new Node;
    new_node->val = node->val;
    // 记录已经clone过当前节点
    my_map[node] = new_node;
    
    // step2 copy 邻居
    for(const auto& neighbor : node->neighbors)
    {
    	// 传进去一个node, 传出来一个node,很经典的一种写法
    	// 对于所有neighbors 进行copy，返回neighbors的clone, 
    	// 至于neighbors的孩子是怎么处理的我们不管，自己调用DFS去建立去
    	// 我们知道的是只要你返回了，那就是已经把自己复制好了
        new_node->neighbors.push_back(helper(neighbor, my_map)); // 关键
    }
    return new_node;
}




// 										Q2 merge k sorted array
// Q2.1 merge k sorted array
// 问面试官是升序 降序

// 法1 merge sort

// 法2， min_heap with k element, pop出最小的，先前移动一位，再将新的元素插入



// 										Q3 BST
// 3.1 Find the node whose value is cloest to the target value
// Method: 
// 维持一个min_diff = |root->val - target|,用于更新globalNode
// case 1: if(root == null) return globalNode
// case 2: if(root->val < target) 看看globalNode能更新就更新，向右边移动
// case 3: if(root->val > target) 看看globalNode能更新就更新，向左边移动
// case 4: if(root->val == target) globalNode = root 返回

// 3.2 largest element in the tree that smaller than the target
// Method: 
// case 1: if(root == null) return globalNode
// case 2: if(root->val >= target) globalNode不更新，向左边移动
// case 3: if(root->val > target) globalNode必须更新，向右边边移动


// 3.3 remove a target node in BST
// 分类讨论
// 先递归遍历找到target (copy graph trick, 输入一个节点，返回处理后的自己) 
// case 1: no child, root is leaf, delete this node. return null
// case 2: only one child left/right. delete this node. return no null child
// case 3: two child
//			3.1 find the smallest in the right tree
// 			3.2 copy smallest to root
//			3.3 Recursive to delete the smallest from the root->right
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
TreeNode* deleteNode(TreeNode* root, int key) {
    if(!root) return nullptr;
    if(root->val > key)
    {
        root->left = deleteNode(root->left, key);
    }else if(root->val < key)
    {
        root->right = deleteNode(root->right, key);
    }else //if(root->val == key)
    {
        if(root->left == nullptr && root->right == nullptr)
        {
            return nullptr;
        }else if(root->left == nullptr || root->right == nullptr)
        {
            return root->left == nullptr ? root->right : root->left;
        }else
        {
            TreeNode* smallest = findSmallest(root->right);
            //TreeNode* new_node = new TreeNode(smallest->val);
            //new_node->left = root->left;
            //new_node->right = root->right;
            root->val = smallest->val;
            root->right = deleteNode(root->right, smallest->val);
            return root;
        }
    }
   return root;
}

TreeNode* findSmallest(TreeNode* root)
{
    if(root->left == nullptr)
    {
        return root;
    }
   return findSmallest(root->left);
}



// 3.4 insert node in BST
// 1 itertaion
// 关键点： 记录一个parent
TreeNode* insertIntoBST(TreeNode* root, int val) {
    TreeNode* new_node = new TreeNode(val);
    if(!root) return new_node;
    TreeNode* parent = root;
    TreeNode* cur = root;
    while(cur)
    {
        parent = cur;
        if(cur->val < val)
        {
            cur = cur->right;  
        }else if(cur->val > val)
        {
            cur = cur->left;
        }
    }
    // cur == nullptr
    if(val < parent->val)
    {
        parent->left = new_node;
    }else
    {
        parent->right = new_node;
    }
    return root;   
}

// 2 recurision
TreeNode* insertIntoBST(TreeNode* root, int val) {
    if(!root)
    {
        return new TreeNode(val);
    }
    if(root->val > val)
    {
        root->left = insertIntoBST(root->left, val);
    }else
    {
        root->right = insertIntoBST(root->left, val);
    }
    return root;
}


// 2D DP. 不看




















































