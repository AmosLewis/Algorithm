main()如果需要等待新thread退出，则新thread实例需要使用join(),

main()如果需要等待新thread，则新thread实例可以使用detach(), 不建议使用detach(),使用后脱离main独自在后台允许，容易导致程序崩溃。

This is the example code

'''

	#include <iostream>

	#include <thread>

	using namespace std;

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
