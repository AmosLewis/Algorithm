[https://yq.aliyun.com/articles/584964]

main()如果需要等待新thread退出，则新thread实例需要使用join(),

main()如果需要等待新thread，则新thread实例可以使用detach(), 不建议使用detach(),使用后脱离main独自在后台允许，容易导致程序崩溃。

This is the example code

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
async is used for more abstracy task. future is used for store value for future process

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
