#ifndef __THREAD_H__
#define __THREAD_H__
#include <iostream>
#include </opt/boost_1_65_1/boost/noncopyable.hpp>
#include <pthread.h>
#include "MutexLock.h"
#include "Condition.h"
class Thread : public boost::noncopyable
{
    public :
        Thread();
        virtual ~Thread();//虚析构
        void start();
        void join();
        virtual void run()=0;//纯虚函数
        pthread_t getThreadId() const
        {
            return threadId_;
        }
    private:
        //pthread_create()第三个参数是一个回调函数，void*为返回值和参数
        static void *runInThread(void *arg);
        pthread_t threadId_;
        bool isRunning_;
};
#endif
