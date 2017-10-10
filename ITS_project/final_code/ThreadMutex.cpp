#include "ThreadMutex.h"
#ifndef _WIN32
ThreadMutex::ThreadMutex()
{
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr,PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&m_mutex,&attr);
    pthread_mutexattr_destroy(&attr);
    m_isLocker = false;
}

ThreadMutex::ThreadMutex(bool isLocker)
{
    ThreadMutex();
    if(isLocker)
    {
        ThreadLock();
    }
    m_isLocker = isLocker;
}

ThreadMutex::~ThreadMutex()
{
    if(m_isLocker)
    {
        UnThreadLock();
    }
    pthread_mutex_destroy(&m_mutex);
}

void ThreadMutex::ThreadLock()
{
    if(!m_isLocker)
    {
        pthread_mutex_lock(&m_mutex);
    }
}

void ThreadMutex::UnThreadLock()
{
    pthread_mutex_unlock(&m_mutex);
}
#endif

