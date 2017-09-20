#include "thread.h"


Thread::Thread():isRunning_(false),threadId_(0){}//构造函数
Thread::~Thread()//析构函数
{
    if(isRunning_)
    {
        CHECK(!pthread_detach(threadId_));//如果线程正在运行，则让其状态为detached
    }
}

void *Thread::runInThread(void *arg)
{
    Thread *pt =static_cast<Thread*>(arg);//arg即为this指针
    pt->run();//调用run方法
    return NULL;
}


void Thread::start()
{
    CHECK(!pthread_create(&threadId_,NULL,Thread::runInThread,this));//创建线程
    isRunning_=true;
}

void Thread::join()
{
    assert(isRunning_);
    CHECK(!pthread_join(threadId_,NULL));//回收线程
    isRunning_=false;
}