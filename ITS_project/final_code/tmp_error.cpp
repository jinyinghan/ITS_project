/**********************************************
*Project:main for ITS
*Author:GenieHan
*Email:hahahaha-oooo@163.com
*Date:2017/09
***********************************************/
/* #include "itsc.h" */
#include "allosthread.h"
#include "ThreadMutex.h"
#include "CppSQLite3.h"
#include <ctime>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

const char* gszFile = "Config.db";
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
int main (int argc,char* argv[])
{
#if 0
	Ring_Queue* default_queue = new Ring_Queua(LOOP_SIZE,sizeof(DATA_TYPE));
    Lets_Config* default_config = new Lets_Config();
    default_config->start();

    Logic_Execute* default_execute = new Logic_Execute();
    default_execute->start();
#endif
//1. 读取默认参数，开始运行
//2.信号量阻塞数据库变更，销毁重建

    try
    {
        int i, fld;
        time_t tmStart, tmEnd;
        CppSQLite3DB db;

        cout << "SQLite Header Version: " << CppSQLite3DB::SQLiteHeaderVersion() << endl;
        cout << "SQLite Library Version: " << CppSQLite3DB::SQLiteLibraryVersion() << endl;
        cout << "SQLite Library Version Number: " << CppSQLite3DB::SQLiteLibraryVersionNumber() << endl;

        remove(gszFile);
        db.open(gszFile);

//        cout << endl << "plan1 table exists=" << (db.tableExists("plan1") ? "TRUE":"FALSE") << endl;


        for (int planNub = 0; planNub < 3; planNub++)
        {
            char buf[128];
/*             sprintf(buf, "create table plan%d(phase_id int, GreenTime int, YellowTime int;", planNub+1); */
            db.execDML(buf);
        }
        cout << endl << "Creating plan1 table" << endl;
        db.execDML("create table plan1(phase_id int, GreenTime int, YellowTime int;");
        cout << endl << "plan1 table exists=" << (db.tableExists("plan1") ? "TRUE":"FALSE") << endl;
        
        cout << endl << "Creating plan2 table" << endl;
        db.execDML("create table plan2(phase_id int, GreenTime int, YellowTime int;");
        cout << endl << "plan2 table exists=" << (db.tableExists("plan2") ? "TRUE":"FALSE") << endl;
        
        cout << endl << "Creating plan3 table" << endl;
        db.execDML("create table plan3(phase_id int, GreenTime int, YellowTime int;");
        cout << endl << "plan3 table exists=" << (db.tableExists("plan3") ? "TRUE":"FALSE") << endl;

        
        
    }
    catch (CppSQLite3Exception& e)
    {
        cerr << e.errorCode() << ":" << e.errorMessage() << endl;
    }
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

}
