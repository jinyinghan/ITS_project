#include "allosthread.h"
#include <assert.h>

ALLOSThread::ALLOSThread()
{
    memset(m_ThreadPoll,0,sizeof(m_ThreadPoll));
    m_iCurThreadCount = 0;
}

ALLOSThread::~ALLOSThread()
{    
}

bool ALLOSThread::CreateThread(ThreadFun pFun,void* pThParam)
{
    if(m_iCurThreadCount >= MAX_THREAD)
    {
        return false;
    }
#ifdef _WIN32
    UINT uiThreadID;
    m_ThreadPoll[m_iCurThreadCount] = (THREAD_HANDLE)(::beginthreadex(NULL,NULL,pFun,pThParam,NULL,&uiThreadID));
    if(NULL == m_ThreadPoll[m_iCurThreadCount])
    {
        assert(0);
        return false;
    }
    m_iCurThreadCount++;
    return true;
#else //!WIN32
    UINT upth;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
    upth = pthread_create(&m_ThreadPoll[m_iCurThreadCount],NULL,pFun,pThParam);
    if(upth)
    {
        assert(0);
        return false;
    }
    pthread_attr_destroy(&attr);
    m_iCurThreadCount++;
    return true;
#endif
}

void ALLOSThread::DestroyThread()
{
#ifdef _WIN32
    for(int i = 0;i < m_iCurThreadCount;i++)
    {
        if(NULL != m_ThreadPoll[m_iCurThreadCount])
        {
            if(WAIT_OBJECT_0 == WaitForSingleObject(m_ThreadPoll[m_iCurThreadCount],INFINITE))
            {
                CloseHandle(m_ThreadPoll[m_iCurThreadCount]);
            }
        }
    }
#else //!_WIN32
    for(int i = 0;i < m_iCurThreadCount;i++)
    {
        pthread_join(m_ThreadPoll[m_iCurThreadCount],NULL);
    }
#endif 
}

