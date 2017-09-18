#ifndef __CAPSULATION_THREAD_H__
#define __CAPSULATION_THREAD_H__

#include <iostream>
#include <pthread.h>
#include "/opt/apr/include/apr-1/apr_thread_proc.h"

class Thread
{
    public:
/*         static const int THREAD_STATUS_NEW = 0; */
        /* static const int THREAD_STATUS_RUNNING = 1; */
        /* static const int THREAD_STATUS_EXIT = -1; */
        
        Thread(bool bDetach = true);
        virtual ~Thread();

        virtual void run() = 0;

        int start();
        int join();
        /* void join(unsigned long millisTime);//等待线程退出或者超时 */
        /* int getState();//获取线程的状态 */
        void destroy();

        int get_thread_id()
        {
            return thr_id_;
        }
        void set_thread_id(unsigned long thrId)
        {
            thr_id_ = thrId;
        }

    protected:
        static void* _stdcall thread_proc(apr_thread_t* th,void* data);
        void notify()
        {
            cond_.signal();
        }
        bool check_interrupt()
        {
            return bExit_;
        }
    private:
        size_t  thr_id_;
        bool    bExit_;

        apr_thread_t*   thr_;
        Condition       cond_;
        /* int             threadStatus;//线程的状态 */
        /* static void* thread_proxy_func(void* args);//获取执行方法的指针 */
        Thread(const Thread& );
        Thread& operator =(const Thread&);
};




#endif // __CAPSULATION_THREAD_H__

