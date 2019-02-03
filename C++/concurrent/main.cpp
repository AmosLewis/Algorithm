#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <cassert>
#include <future>
#include <string>
#include <chrono>
#include <condition_variable>
#include <deque>
#include <mutex>
//#include <boost/filesystem.hpp>
//#include <experimental/filesystem>
using namespace std;

#define NUM_THREADS 10

template <typename T>
class MsgQueue
{
    deque<T> _queue;
    condition_variable _cond;
    mutex _mutex;
public:
    void send(T && msg)
    {
        {
            lock_guard<mutex> lck;
            _queue.push_front(move(msg));
        }
        _cond.notify_one();
    }

    T receive()
    {
        unique_lock<mutex> lck(_mutex);
        _cond.wait(lck, [this]{return !_queue.empty();});
        T msg = move(_queue.back());
        _queue.pop_back();
        return msg;
    }
};

void listDirServer(MsgQueue<path> & dirQueue, MsgQueue<string> & fileQueue)
{
    for(;;)
    {
        path dir = dirQueue.receive();

        for(directory_iterator it(dir); it != directory_iterator(); it++)
        {
            if(it->is_directory())
            {
                dirQueue.send(it->path());
            }else
            {
                fileQueue.send(it->path().filename);
            }
        }
    }
}

void printServer(MsgQueue<string> & nameQueue)
{
    for(;;)
    {
        string name = nameQueue.receive();
        cout<<name<<endl;
    }
}

void listTree(path && rootdir)
{
    MsgQueue<path> & dirQueue;
    MsgQueue<string> & fileQueue;
    dirQueue.send(move(rootdir));

    vector<future> futures;
    for(int i = 0; i < NUM_THREADS; i++)
    {
        futures.push_back(async(launch::async, &listDirServer,
            ref(dirQueue), ref(fileQueue)));
    }

    futures.push_back(async(launch::async, &printServer,
                            ref(fileQueue)));

    try
    {
        while(!futures.empty())
        {
            auto ftr = move(ftr.back);
            futures.pop_back();
            ftr.get();
        }
    }
    catch (exception & e)
    {
        cout<<e.what()<<endl;
    }
    catch(...)
    {
        cout<<"unknow exception"<<endl;
    }


}

int main()
{
    return 1;
}



//// task based currency
//// task stealing
//int main()
//{
//    cout<<"main thread ID " << this_thread::get_id()<<endl;
//    vector<future<void>> futures;
//    for(int i = 0; i < 10; i++)
//    {
//        auto ftr = async([](){
//            this_thread::sleep_for(chrono::seconds(1));
//            cout<<this_thread::get_id()<<" ";
//        });
//        futures.push_back(move(ftr));
//    }
//
//    for_each(futures.begin(), futures.end(), [](future<void> & ftr)
//    {
//        ftr.wait();
//    });
//
//    cout<<endl;
//    this_thread::sleep_for(chrono::seconds(10));
//
//    return 0;
//}
//// main thread ID 0x107d405c0
//// 0x700006231000 0x7000061ae000  0x700006337000 0x7000063ba000 0x7000062b4000 0x70000643d000 0x7000064c0000 0x7000065c6000 0x700006543000 0x700006649000


//// async
//// simplify the promise and future
//// simplify the exception
//// Same as the normal function
//string Fun()
//{
//    string str("string from future ");
//    throw(exception());
//    return str;
//}
//
//int main()
//{
////    promise<string> prms;
////    future<string> ftr = prms.get_future();
////    thread th(&thFun, move(prms));
//    auto ftr = async(&Fun);
//    cout<<"str from main"<<endl;
//    try
//    {
//        string str = ftr.get(); // 如果还没有 prms.set_value(str)， main将会阻塞在这里
//        cout<<str<<endl;
//    } catch (exception & e)
//    {
//        cout<<e.what()<<endl;
//    }
////    th.join();
//    return 0;
//}
//// str from main
//// std::exception


//// async
//// simplify the promise and future
//string Fun()
//{
//    string str("string from future ");
//    return str;
//}
//
//int main()
//{
////    promise<string> prms;
////    future<string> ftr = prms.get_future();
////    thread th(&thFun, move(prms));
//    auto ftr = async(&Fun);
//    cout<<"str from main"<<endl;
//    string str = ftr.get(); // 如果还没有 prms.set_value(str)， main将会阻塞在这里
//    cout<<str<<endl;
////    th.join();
//    return 0;
//}
//// str from main
//// string from future


//// promise and future
//// exception
//void thFun(promise<string> && prms)
//{
//    try
//    {
//        string str("string from future");
//        throw(exception());
//        prms.set_value(str);
//    }catch(...)
//    {
//        prms.set_exception(current_exception());
//    }
//
//}
//
//int main()
//{
//    promise<string> prms;
//    future<string> ftr = prms.get_future();
//    thread th(&thFun, move(prms));
//    cout<<"str from main"<<endl;
//    try
//    {
//        string str = ftr.get(); // 如果还没有 prms.set_value(str)， main将会阻塞在这里
//        cout<<str<<endl;
//    }catch (exception & e)
//    {
//        cout<<e.what()<<endl;
//    }
//    th.join();
//    return 0;
//}
// str from main
// std::exception



//// promise and future
//// promise pass by reference
//void thFun(promise<string> & prms)
//{
//    string str("string from future");
//    cout<<"promise str address:"<<(void*)str.data()<<endl;
//    prms.set_value(str);
//}
//
//int main()
//{
//    promise<string> prms;
//    thread th(&thFun, ref(prms));
//    cout<<"string from main "<<endl;
//    future<string> ftr = prms.get_future();
//    string str = ftr.get(); // 如果还没有 prms.set_value(str)， main将会阻塞在这里
//    cout<<str<<endl;
//    cout<<"main str address:"<<(void*)str.data()<<endl;
//    th.join();
//    return 0;
//}
//// string from main
//// promise str address:0x700006e23bb9
//// string from future
//// main str address:0x7ffeed988831



//// promise and future
//// promise pass by move
//void thFun(promise<string> && prms)
//{
//    string str("string from future");
//    prms.set_value(str);
//}
//
//int main()
//{
//    promise<string> prms;
//    future<string> ftr = prms.get_future();
//    thread th(&thFun, move(prms));
//    cout<<"str from main"<<endl;
//    string str = ftr.get(); // 如果还没有 prms.set_value(str)， main将会阻塞在这里
//    cout<<str<<endl;
//    th.join();
//    return 0;
//}
//// str from main
//// string from future


//// Dangling reference
//void thFun(int &i)
//{
//    cout<<"thread "<<i<<endl;
//}
//
//void test(vector<thread>&  workers)
//{
//    for(int i = 0; i < 8; i++)
//    {
//        auto th = thread(&thFun, ref(i));
//        /*
//         * thread 5thread
//         * thread 6Hello, World!
//         *
//         * thread 71536
//         * thread thread 1536
//         * thread 1536
//         *
//         * thread 0
//         * 1536
//         * 传reference 到thread很危险
//         * 每一个thread有一个自己的 stack, 传引用会复制一个指针到该thread的stack上
//         */
//
//        workers.push_back(move(th));
//        assert(!th.joinable());
//    }
//}
//
//int main() {
//    vector<thread> workers;
//
//    test(workers);
//
//    std::cout << "Hello, World!" << std::endl;
//    for_each(workers.begin(), workers.end(), [](thread& th){
//        assert(th.joinable());
//        th.join();
//    });
//
//    return 0;
//}


//// lamda version
//int main() {
//    vector<thread> workers;
//    for(int i = 0; i < 8; i++)
//    {
//        auto th = thread([i](){
//            cout<<"thread "<<i<<endl;
//        });
//
//        workers.push_back(move(th));
//        assert(!th.joinable());
//    }
//
//    std::cout << "Hello, World!" << std::endl;
//    for_each(workers.begin(), workers.end(), [](thread& th){
//        assert(th.joinable());
//        th.join();
//    });
//
//    return 0;
//}