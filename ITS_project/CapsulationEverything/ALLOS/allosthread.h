#ifndef _ALLOSTHREAD_H
#define _ALLOSTHREAD_H
#include <string.h>
#ifndef ULONG
 typedef unsigned long ULONG;
#endif
#ifndef UINT
 typedef unsigned int UINT;
#endif

#ifdef WIN32
#define _AFXDLL
#include <process.h>
#include <afx.h>

#define THFNRETURN unsigned int
#define STDCALL _stdcall
#define THREAD_HANDLE HANDLE

#else //!WIN32
#include <pthread.h>

#define  THFNRETURN void*
#define STDCALL
#define THREAD_HANDLE pthread_t
#endif

typedef THFNRETURN (STDCALL *ThreadFun)(void*);

#define MAX_THREAD 5

class ALLOSThread
{
    public:
    ALLOSThread();
    virtual ~ALLOSThread();
    virtual bool CreateThread(ThreadFun,void* pThParam);
    virtual void DestroyThread();
    private:
    THREAD_HANDLE m_ThreadPoll[MAX_THREAD];
    int m_iCurThreadCount;
};

#endif //_ALLOSTHREAD_H