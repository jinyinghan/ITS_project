#include "capsulation_thread.h"

Thread::start()
{
    apr_status_t    rv;
    apr_threadattr_t*   thrattr = NULL;
    apr_threadattr_create(&thrattr,g_mpool);

    if(rv = apr_thread_create(&thr_,thrattr,Thread::Thread_proc,this,g_mpool)) != APR_SUCCESS)
    {
        set_error_code(rv);
        char errbuf[512];
        apr_strerror(rv,errbuf,sizeof(errbuf));
        log2DebufView("Thread:failed create a thread:[%d][%s]\n",rv,errbuf);
        return rv;
    }
    apr_sleep(100000);
    return rv;
}

int Thread::join()
{
    bExit_ = true;
    notify();
    apr_sleep(100000);

    apr_status_t rv = 0;
    return apr_thread_join(&rv,thr_);

}

void Thread::destroy()
{
    if(!bExit_)
    {
        join();
        cond_.destroy();
    }
}

void* Thread::thread_proc(apr_thread_t* th,void* data)
{
    Thread* pthis = static_cast<Thread*>(data);
    while(!pthis -> bExit_)
    {
        pthis -> run();
        pthis -> cond_.wait();
    }
    printf("thread exit,id:%d\n",pthis ->get_thread_id());
    apr_thread_exit(th,APR_SUCCESS);
    return NULL:

}
