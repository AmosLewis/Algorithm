// Topic1 stack
// Q1
// implement queue with 2 stack
class MyQueue{
	void push(const int& i)
	{
		s1.push(i);
		return;
	}
	int void pop()
	{
		int a;
		if(s2.empty())
		{
			while(!s1.empty())
			{
				s2.push(s1.top());
				s1.pop();
			}
			
			a = s2.top();
			s2.pop();
		}else
		{
			int a = s2.top();
			s2.pop();
		}
		return s2.empty() ? -1 : a;
	}

private:
	stack<int> s1; // used to buffer all new elements
	stack<int> s2; // used to pop 1 first element
	// case2.1 If s2 is empty, push all elements in s1 into s2, then pop the top of the s2
	// case2.2 If s2 is not empty, pop the top element of s2
	// amortizied time complexity = O(1)
	// [n+n+1+(n-1)] / n = 3 = O(1) 
}

// Q2
// min stack
class minStack{
public:
	int add(int a)
	{
		s1.push(a);
		if(a < min_val)
		{
			min_val = a;
		}
		s2.push(min_val);
	}
	int remove()
	{
		int temp = min_val;
		s1.pop();
		s2.pop();
		min_val = s2.top();
		return temp;
	}

private:
	stack<int> s1; // used to buffer all new elements
	stack<int> s2; // used to store correspondant min value
	int min_val = INT_MAX; // global min value
	// keep add and remove in sync between stack1 and stack 2
}
// follow up
// if stack1 with too many repeat value?how to optimize the space 
// complexity of stack2
class minStackRepeat{
public:
	int add(int a)
	{
		s1.push(a);
		if(a < min_val)
		{
			s2.push(make_pair<a, s1.size()>);
			min_val = a;
		}
	}
	int remove()
	{
		s1.pop();
		int a;
		a = s2.top().first;
		if(s1.size() == s2.top().second)
		{
			s2.pop();
			min_val = s2.top().first;
		}
		return a;
	}

private:
	stack<int> s1; // used to buffer all new elements
	stack<pair<int, int>> s2; // used to first occurence of every min value
	int min_val = INT_MAX;
	// 2 2 2 1 1 3 5
	// <2,1> <1, 3> 
}

// Q3
// 2 stack implement selected sort
vector<int> selectedSort2Stack(vector<int>& nums)
{
	stack<int> s1;
	stack<int> s2;
	int global_min;
	for(int i = 0; i < nums.size(); i++)
	{
		int a = nums[i];

	}
}



// reverse linkded list
class ListNode{
	int val;
	ListNode* next;
	ListNode(): val(0), next(nullptr){}
}

ListNode* reverseList(ListNode* head)
{
	if(head == nullptr || head.next == nullptr) return head;
	// 全局变量
	ListNode* pre = nullptr;
	ListNode* cur = head;

	while(cur != nullptr)
	{
		ListNode* next = head->next; // store next 用于下一次更新cur, 局部变量
		// 每一次reverse一个
		cur->next = pre;
		pre = cur;
		cur = next;
	}
	return pre;
}

ListNode* reverseList(ListNode* head)
{
	// n1 n2 n3
	//       head
	if(head == nullptr || head.next == nullptr) return head;
	// head
	// cur | next .......

	ListNode* next = head->next;
	ListNode* cur = head;

	ListNode* new_head = reverseList(head->next);

	next->next = cur;
	cur->next = nullptr;

	return new_head;
}
// example
// 1st call: null n1 -> n2 -> n3
//               cur   next
// 2st call: null n1 -> n2 -> n3
//						cur	  next
// 3st call: null n1 -> n2 -> n3
//							  cur next	
// ===================================
// 2st call: null n1 -> n2 <- n3
//						cur	  next
//							  new_head
// 1st call null<-n1 <- n2 <- n3
//				 cur	next
//							  new_head


// find middle of listNode
ListNode* findMiddle(ListNode* head)
{
	if(head == nullptr)
	{
		return nullptr;
	}

	ListNode *slow = head, *fast = head;
	while(fast->next != nullptr && fast->next->next != nullptr)
	{
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow
}
// 1 2 3 4 5 null
// s/f
// 	 s f
//     s   f
// 1 2 3 4 5 6 null
// s/f
// 	 s f
//     s   f


// merge 2 sorted list
ListNode* merge2List(listNode* l1, listNode* l2)
{
	ListNode temp;
	ListNode* head = &temp;
	while(l1 != nullptr || l2 != nullptr)
	{
		if(l1.val <= l2.val)
		{
			head->next = l1;
		}else
		{
			head->next = l2;
		}
		head = head->next;
	}
	if(l1)
	{
		head->next = l1;
	}
	if(l2)
	{
		head->next = l2;
	}
	return temp->next;
}


// sort nums with 2 stack
// 3 1 2 2 2 4
// global_min = 
// counter = 
// s1|| 3 1 2 2 2 4
// s2|| 

// global_min = 4
// counter = 1
// s1|| 3 1 2 2 2 
// s2|| 4

// global_min = 2
// counter = 1
// s1|| 3 1 2 2  
// s2|| 4 2

// global_min = 2
// counter = 2
// s1|| 3 1 2  
// s2|| 4 2 2

// global_min = 2
// counter = 3
// s1|| 3 1  
// s2|| 4 2 2 2

// global_min = 1
// counter = 1
// s1|| 3 
// s2|| 4 2 2 2 1

// global_min = 1
// counter = 1
// s1|| 
// s2|| 4 2 2 2 1 3

// global_min = 1
// counter = 1
// s1|| 3 
// s2|| 4 2 2 2  

// global_min = 1
// counter = 1
// s1|| 3 2 2 2 4
// s2||  

// global_min = 1
// counter = 1
// s1|| 3 2 2 2 4
// s2|| 1|

// 以上为第一轮
// 记录 s2.size() = 1

// global_min = 
// counter = 
// s1|| 3 2 2 2 4
// s2|| 1|

// global_min = 4
// counter = 1
// s1|| 3 2 2 2 
// s2|| 1| 4

// global_min = 4
// counter = 1
// s1|| 3 2 2 2 
// s2|| 1| 4

// global_min = 2
// counter = 3
// s1|| 
// s2|| 1| 4 2 2 2 3

// global_min = 2
// counter = 3
// s1|| 3 4
// s2|| 1| 

// global_min = 2
// counter = 3
// s1|| 3 4
// s2|| 1 2 2 2 |

// 第二轮循环完了
// s2.size() == 4



// 用int array 实现circular Queue
class CircleQueue{
public:
	CircleQueue(int qsize)
	{
		// 初始化队列的数组大小为qsize
		m_queue = new int[qsize];
		m_queue_size = qsize;
	}

	~CircleQueue()
	{
		delete[] m_queue;
	}

	bool push(int a)
	{
		// 如果元素被满了，不存放
		if(size == m_queue_size)
		{
			return false;
		}else
		{
			m_queue[end] = a;
			// end + 1 越过右边界， 设置end为0
			end = end + 1 == m_queue.size() ? 0 : end + 1;
			size++;
			return true;
		}
	}

	int pop()
	{
		if(size == 0)
		{
			return INT_MIN;
		}

		int result = array[front];
		// front + 1 越过右边界，设置为0
		front = front+1 == m_queue_size ? 0 : front + 1;
		size--;
		return result;
	}

	int top()
	{
		// 没有元素
		if(size == 0)
		{
			return INT_MIN;
		}
		return m_queue[front];
	}

private:
	// circular array
	int* m_queue;
	int m_queue_size;
	int front = 0, int end = 0; // front 指向第一个元素，end指向下一个可以插入的位置
	int size; // 已经存放的元素的个数
}




