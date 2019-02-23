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
