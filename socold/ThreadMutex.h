#ifndef __THREADMUTEX_H
#define __THREADMUTEX_H

#ifdef __WIN32
#include <windows.h>
class ThreadMutex
{
    private:
        CRITICAL_SECTION    m_mutex;
        bool                m_isLocker;
    public:
        ThreadMutex()
        {
            ::InitializeCriticalSection(&m_mutex);
        }
        
        ThreadMutex(bool isLocker)
        {
            ThreadMutex();
            if(isLocker)
            {
                ThreadLock();
            }
            m_isLocker = isLocker;            
        }
        
        ~ThreadMutex()
        {
            if(m_isLocker)
            {
                UnThreadLock();
            }
            ::DeleteCriticalSection(&m_mutex);
        }

        void ThreadLock()
        {
            if(!m_isLocker)
            {            
                ::EnterCriticalSection(&m_mutex);
            }
        }

        void UnThreadLock()
        {
            ::LeaveCriticalSection(&m_mutex);
        }

};
#else
#include <pthread.h>
class ThreadMutex
{
    private:
        pthread_mutex_t     m_mutex;
        bool                m_isLocker;
    public:
        ThreadMutex();
        ThreadMutex(bool isLocker);
        ~ThreadMutex();
        void ThreadLock();
        void UnThreadLock();
};
#endif



#endif //__THREADMUTEX_H
