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
	#include <condition_variable>
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