#include "allosthread.h"
#include "ThreadMutex.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int iCount = 0;
ThreadMutex mutex;

THFNRETURN STDCALL ThreadFunc1(void* pParam)
{
    while(1)
    {
        mutex.ThreadLock();
        printf("ThreadFunc1 Running :%d ~\n",iCount);
        iCount++;
        mutex.UnThreadLock();
        printf("ThreadFunc1 sleep 2s ========>>>>\n");
        sleep(2);
    }
    return NULL;
}

THFNRETURN STDCALL ThreadFunc2(void* pParam)
{
    while(1)
    {
        mutex.ThreadLock();
        printf("ThreadFunc2 Running :%d ~\n",iCount);
        iCount++;
        mutex.UnThreadLock();
        printf("ThreadFunc2 sleep 1s ========>>>>\n");
        sleep(1);
    }
    return NULL;
}

int main(int argc,char* argv[])
{
    ALLOSThread* pThread = new ALLOSThread;
    if(pThread != NULL)
    {
        pThread->CreateThread(ThreadFunc1,NULL);
        pThread->CreateThread(ThreadFunc2,NULL);
    }
    else
    {
        delete pThread;
        pThread = NULL;
    }
    while(1);
     
}
