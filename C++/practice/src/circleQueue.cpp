/**
 * NOTE: It's preferred that the coder avoids using any of the C++
 * Standard Template Library for this challenge.
 *
 * A FIFO fixed size circular queue of chars.  The necessary memory should
 * be allocated at creation and released at deconstruction, it should
 * stay static at all other times.  If more than `size` characters are
 * pushed onto the queue, the characters should circle back to the
 * beginning and overwrite those positions.
 *
 * Example for buffer of size 3 ("x" means empty):
 * Initial state: [x x x]
 * enqueue 'a': ['a' x x]
 * enqueue 'b': ['a' 'b' x]
 * enqueue 'c': ['a' 'b' 'c']
 * enqueue 'd': ['b' 'c', 'd']
 * dequeue: return 'b', ['c' 'd' x]
 * dequeue: return 'c', ['d' x x]
 * enqueue 'e', ['d' 'e' x]
 * dequeue: return 'd', ['e' x x]
 */
template<typename T>
class CircularQueue
{
public:
    /// Initialize the queue with a given size
    CircularQueue (int buffer_size)
    {
        // TODO
	  rear = front = -1;
        size = buffer_size;
        arr = new T[buffer_size];
    }

    ~CircularQueue ()
    {
        // TODO
 	  delete arr[];
    }

    /// Adds one element to the queue, replacing the oldest element if the queue is full
    void enqueue(const T& element)
    {
        // TODO
	  if(front == 0 && rear = size -1 || rear == (front-1)%(size() - 1))
	  {
		// full 
		arr[front] = element;
		
		if(front == size - 1)
		{
			front = 0;
}else
{
			front++;
		}
		
		if(rear == size - 1)
		{
rear = 0;
}
else
{
	rear++;
}
		
		return;
        }
  else if(front == -1)
  {
	front = rear = 0;
	arr[rear] =element;
  }
	  else if(rear = size() -1 && front != 0)
	  {
		rear = 0;
		arr[rear] = element;
        }
        else
	  {
		rear++;
		arr[rear] = element;
  }
        
    }

    /// Returns the oldest element and removes it from the queue
    T dequeue()
    {
        // TODO 
        if(front == -1)
	  {
		// empty
		return T();
  }
  T data = arr[front];
  arr[front] = -1;
  if(front == rear)
  {
	front = -1;
      rear = -1;
  }
  else if(front == size-1)
  {
	front = 0;
  }
  else
  {
	front++;
  }
	 
        return data;
    }

    /// Return the number of elements currently in the queue
    int count()
    {
        // TODO
	  if(rear>=front)
        return -1;
    }

    /// Return the size of the queue's buffer
    int size()
    {
        // TODO
        return -1;
    }

private:
    /// Add any variables needed to complete this challenge here.
    int rear, front;
    int size;
    T* arr;
};


