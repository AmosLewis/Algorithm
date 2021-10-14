// implement queue with 2 stack
// Q1 2 stack -> queue
template <class T>
class MyQueue
{
public:
	void push(T a)
	{
		s1.push(a);
	}

	T pop()
	{
		if(s2.empty() && s1.empty())
		{
			return -1;
		}

		if(s2.empty())
		{
			while(!s1.empty())
			{
				s2.push(s1.top());
				s1.pop();
			}
		}
		T a = s2.top();
		s2.pop();
		return a;
	}
private:
	stack<T> s1;
	stack<T> s2;
}
// Amortized time is O(1)


// Q2
// 2 stack -> min






listoperation.cpp
class ListNode{
	int val;
	ListNode* next;
	ListNode(int a): val(a), next(nullptr){}
}

// length()
int length(ListNode* head)
{
	ListNode* temp = head;
	int length = 0;
	while(temp != nullptr)
	{
		length++;
		temp = temp->next;
	}
	// temp = nullptr
	return length;
}

// get(index)
ListNode* get(ListNode* head, int index)
{
	ListNode* temp = head;
	while(temp != nullptr && index > 0)
	{
		temp = temp->next;
		index--;
	}

	// index <= 0 || temp == nullptr
	return temp;
}


// virtual function 运行时期确定改函数偏移量，用vitual table 找到，
// VPTR指向 vtable
// VPTR的状态是由被最后调用的构造函数确定的




