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
#include "Linklist.h"  
#include <ctime>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>  
#include <unistd.h>

using namespace std;

const char* gszFile = "Config.db";
int iCount = 0;
ThreadMutex mutex;
CppSQLite3DB db;
LinkList head;  
Info val1,val2,val3,val4;  

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

void init_Config_sqlite()
{
    try
    {
        cout << "SQLite Header Version: " << CppSQLite3DB::SQLiteHeaderVersion() << endl;
        cout << "SQLite Library Version: " << CppSQLite3DB::SQLiteLibraryVersion() << endl;
        cout << "SQLite Library Version Number: " << CppSQLite3DB::SQLiteLibraryVersionNumber() << endl;

        remove(gszFile);
        db.open(gszFile);
    }    
    catch (CppSQLite3Exception& e)
    {
        cerr << e.errorCode() << ":" << e.errorMessage() << endl;
    } 
}

void create_dConfig_table()
{
    try
    {
    
        cout << endl << "Creating plan1 table" << endl;
        db.execDML("create table plan1(phase_id int, GreenTime int,YellowTime int);");
        cout << endl << "plan1 table exists=" << (db.tableExists("plan1") ? "TRUE":"FALSE") << endl;
        cout << endl << "Creating plan2 table" << endl;
        db.execDML("create table plan2(phase_id int, GreenTime int,YellowTime int);");
        cout << endl << "plan1 table exists=" << (db.tableExists("plan2") ? "TRUE":"FALSE") << endl;
        cout << endl << "Creating plan3 table" << endl;
        db.execDML("create table plan3(phase_id int, GreenTime int,YellowTime int);");
        cout << endl << "plan3 table exists=" << (db.tableExists("plan3") ? "TRUE":"FALSE") << endl;
        cout << endl << "Creating dConfig table" << endl;
        db.execDML("create table dConfig(time int, planNub int,phase_sequence int);");
        cout << endl << "plan3 table exists=" << (db.tableExists("dConfig") ? "TRUE":"FALSE") << endl;
    }
    catch (CppSQLite3Exception& e)
    {
        cerr << e.errorCode() << ":" << e.errorMessage() << endl;
    }
}

void init_dConfig_linklist()
{
    val1.id = 1,
    val1.name = Info::close,
    val1.dTime = 2,
    
    val2.id = 2,
    val2.name = Info::red,
    /* val2.dTime = 4, */
    
    val3.id = 3,
    val3.name = Info::green,
    val3.dTime = 11,
    
    val4.id = 4,
    val4.name = Info::yellow,
    val4.dTime = 2;  

//    灯序  
    cout<<"Insert test:"<<endl;  
    head.InsertHead(val1);  
    head.Insert(val3,1);  
    head.Insert(val4,2);  
    head.Insert(val2,3);  
    head.Insert(val4,4);  
}

void linklist_to_dconfigDB()
{
        int nRows = db.execDML("insert into plan1 values (1,11,2);");
        cout << nRows << " rows inserted" << endl;
        nRows = db.execDML("insert into plan1 values (2,12,2);");
        cout << nRows << " rows inserted" << endl;
        nRows = db.execDML("insert into plan1 values (3,13,2);");
        cout << nRows << " rows inserted" << endl;
        nRows = db.execDML("insert into plan1 values (4,14,2);");
        cout << nRows << " rows inserted" << endl;

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
    init_Config_sqlite();

    create_dConfig_table();

    init_dConfig_linklist();

    linklist_to_dconfigDB();
    
    while(1)
    {
        head.Print();  
        cout<<"CircleTime is "<<head.GetCircleTime()<<"s"<<endl;
    }
//2.信号量阻塞数据库变更，销毁重建

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
