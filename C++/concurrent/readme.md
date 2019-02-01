[https://yq.aliyun.com/articles/584964]

main()如果需要等待新thread退出，则新thread实例需要使用join(),

main()如果需要等待新thread，则新thread实例可以使用detach(), 不建议使用detach(),使用后脱离main独自在后台允许，容易导致程序崩溃。

This is the example code


### std::thread

'''

	void my_thread1(int n)
	{
	    for(int i = 0; i < 5; i++)
	    {
		    cout<<"my_thread: Hello, world!"<< n <<endl;
	    }
	}

	int main()
	{
	    cout << "Main: Hello, world!" << endl;

		thread t1(my_thread1, 1);
		thread t2(my_thread1, 2);
		t1.join();
		t2.join();

	    //return 0;
	}

'''


### std::mutex
	
The mutex class is a synchronization primitive that can be used to protect shared data from being simultaneously accessed by multiple threads.

mutex offers exclusive, non-recursive ownership semantics:

A calling thread owns a mutex from the time that it successfully calls either lock or try_lock until it calls unlock.

When a thread owns a mutex, all other threads will block (for calls to lock) or receive a false return value (for try_lock) if they attempt to claim ownership of the mutex.

A calling thread must not own the mutex prior to calling lock or try_lock.
The behavior of a program is undefined if a mutex is destroyed while still owned by any threads, or a thread terminates while owning a mutex. The mutex class satisfies all requirements of Mutex and StandardLayoutType.

std::mutex is neither copyable nor movable.

'''

	mutex m;

	void my_thread1(int n)
	{
	    for(int i = 0; i < 5; i++)
	    {
		lock_guard<mutex> lk(m);
		    cout<<"my_thread: Hello, world!"<< n <<endl;
	    }

	    }

	int main()
	{
	    cout << "Main: Hello, world!" << endl;

		thread t1(my_thread1, 1);
		thread t2(my_thread1, 2);
		t1.join();
		t2.join();

	    //return 0;
	}
'''

### std::unique_lock
The class unique_lock is a general-purpose mutex ownership wrapper allowing deferred locking, time-constrained attempts at locking, recursive locking, transfer of lock ownership, and use with condition variables.

The class unique_lock is movable, but not copyable -- it meets the requirements of MoveConstructible and MoveAssignable but not of CopyConstructible or CopyAssignable.

The class unique_lock meets the BasicLockable requirements. If Mutex meets the Lockable requirements, unique_lock also meets the Lockable requirements (ex.: can be used in std::lock); if Mutex meets the TimedLockable requirements, unique_lock also meets the TimedLockable requirements.


'''

	mutex m;

	void my_thread1()
	{
	    unique_lock<mutex> lck(m, try_to_lock);
	    cout<<(lck.owns_lock() ? '*' : 'X');
	}

	int main()
	{
	    cout << "Main: Hello, world!" << endl;

	    vector<thread> threads;
	    for(int i = 0; i < 50; i++)
	    {
		threads.emplace_back(my_thread1);
	    }

	    for(auto& t: threads)
	    {
		t.join();
	    }

	    //return 0;
	}
'''

### std::condition_variable

The condition_variable class is a synchronization primitive that can be used to block a thread, or multiple threads at the same time, until another thread both modifies a shared variable (the condition), and notifies the condition_variable.


'''

	#include <iostream>
	#include <thread>
	#include <mutex>
	#include <vector>
	#include <condition_variable> // communication between thread
	using namespace std;

	mutex m;
	condition_variable cv;

	void my_thread1()
	{
	    unique_lock<mutex> lck(m);
	    cout<<"waiting"<<endl;// protect by lock
	    cv.wait(lck);
	    cout<<"wake up"<<endl;
	}

	void my_thread2()
	{
	    {
		lock_guard<mutex> lck(m);
		cout<<"notify"<<endl;
	    }
	    cv.notify_one();
	}



	int main()
	{
	    cout << "Main: Hello, world!" << endl;

	    thread t1(my_thread1);
	    thread t2(my_thread2);

	    t1.join();
	    t2.join();

	    //return 0;
	}
'''


### Semaphore hand-definied

'''

	#include <iostream>
	#include <thread>
	#include <mutex>
	#include <vector>
	#include <condition_variable>
	using namespace std;


	class Semaphore
	{
	    mutex m;
	    condition_variable cv;
	    int m_value;
	public:
	    Semaphore(int init): m_value(init){}

	    void post();
	    void wait();

	};

	void Semaphore::post()
	{
	    {
		unique_lock<mutex> lck(m);
		cout<<"post"<<endl;
		++m_value;
	    }
	    cv.notify_one(); // if notify_all, consume a lot of CPU
	}

	void Semaphore::wait()
	{
	    unique_lock<mutex> lck(m);
	    cout<<"wait"<<endl;
	    while(m_value == 0)
	    {
		cv.wait(lck);
	    }
	    --m_value;
	}



	int main()
	{
	    cout << "Main: Hello, world!" << endl;

		Semaphore m_Semaphore(0);

	    thread t1(&Semaphore::post, &m_Semaphore);
	    thread t2(&Semaphore::wait, &m_Semaphore);

	    t1.join();
	    t2.join();

	    //return 0;
	}
	//Main: Hello, world!
	//wait
	//post

'''

### std::async && std::future

async is used for more abstracy task. future is used for store value for future process.

The template function async runs the function f asynchronously (potentially in a separate thread which may be part of a thread pool) and returns a std::future that will eventually hold the result of that function call.

std::future provides a mechanism to access the result of asynchronous operations:

'''

	#include <iostream>
	#include <thread>
	#include <mutex>
	#include <vector>
	#include <condition_variable>
	#include <future>
	#include <chrono>
	using namespace std;

	int func()
	{
	    cout<<__func__<<" is running"<<endl;
	    this_thread::sleep_for(chrono::seconds(1));
	    cout<<"ans is ready"<<endl;
	    return 42;
	}


	int main()
	{
	    cout << "Main: Hello, world!" << endl;

	    future<int> ans = async(launch::async, func);
	    this_thread::sleep_for(chrono::milliseconds(100));
	    cout<<__func__<<" is running." << endl;
	    cout<<ans.get()<<endl;

	    return 0;
	}

'''


### std::promise

'''

	#include <vector>
	#include <thread>
	#include <future>
	#include <numeric>
	#include <iostream>
	#include <chrono>

	void accumulate(std::vector<int>::iterator first,
			std::vector<int>::iterator last,
			std::promise<int> accumulate_promise)
	{
	    int sum = std::accumulate(first, last, 0);
	    accumulate_promise.set_value(sum);  // Notify future
	}

	void do_work(std::promise<void> barrier)
	{
	    std::this_thread::sleep_for(std::chrono::seconds(1));
	    barrier.set_value();
	}

	int main()
	{
	    // Demonstrate using promise<int> to transmit a result between threads.
	    std::vector<int> numbers = { 1, 2, 3, 4, 5, 6 };
	    std::promise<int> accumulate_promise;
	    std::future<int> accumulate_future = accumulate_promise.get_future();
	    std::thread work_thread(accumulate, numbers.begin(), numbers.end(),
				    std::move(accumulate_promise));
	    accumulate_future.wait();  // wait for result
	    std::cout << "result=" << accumulate_future.get() << '\n';
	    work_thread.join();  // wait for thread completion

	    // Demonstrate using promise<void> to signal state between threads.
	    std::promise<void> barrier;
	    std::future<void> barrier_future = barrier.get_future();
	    std::thread new_work_thread(do_work, std::move(barrier));
	    barrier_future.wait();
	    new_work_thread.join();
	}

'''
