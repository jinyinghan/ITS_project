#include "CppSQLite3.h"
#include "allosthread.h"
/* #include "its.h" */
/* #include "ThreadMutex.h" */
/* #include "Linklist.h"   */
#include <iostream>
#include <ctime>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
using namespace std;
typedef unsigned char       uint8_t;
union GRY
{
    uint8_t c[4];
    int d;
};
    union GRY data;

sem_t bin_sem;
const char* gszFile = "Config.db";
/* int iCount = 0; */
CppSQLite3DB db;
/* LinkList head;   */
/* uint8_t YellowTimeBuf[4]; */
/* uint8_t GShackTimeBuf[4]; */
/* uint8_t GreenTimeBuf[4]; */
int ChannelIDbuf[8] = {1,2,3,4,5,6,7,8};
int table1[4][2] = {0};
int table2[4][2] = {0};
int divNow = 0;
int TimeBuf[3][2] = {0};//{0,10,16};

/* Info val1,val2,val3,val4;   */

THFNRETURN STDCALL ThreadFunc1(void* pParam)
{
    while(1)
    {
        sem_wait(&bin_sem);
        cout<<"Change PLan now ,it will start before the circle end"<<endl;
        db.open(gszFile);
try
{
        CppSQLite3Query PLquery;    
        if(divNow == 1)
        {
            PLquery = db.execQuery("select * from plan1");    
        }
        else if(divNow == 2)
        {
            PLquery = db.execQuery("select * from plan2");    
        }
        else
        {
            PLquery = db.execQuery("select * from plan3");    
        }
        int t = 0;
        while(!PLquery.eof())
        {
            table2[t][0]= PLquery.getIntField("GreenTime");
            printf("change plan %d :greenTimetable %d\n",divNow,table2[t][0]);
            t++;
            PLquery.nextRow();    
        }
        PLquery.finalize();    
        t = 0;
}
        catch (CppSQLite3Exception& e)
        {
            cerr << e.errorCode() << ":" << e.errorMessage() <<" B3 error"<< endl;
        }
    db.close();    

    }
}
double get_div_seconds(uint8_t nextDivHours,uint8_t nextDivMin)
{

    time_t timep,nowTime;
    struct tm *p;
    time(&timep);
    p=localtime(&timep);
    p->tm_hour = nextDivHours;
    p->tm_min = nextDivMin;
    p->tm_sec  = 0;
    printf("%s",asctime(p));
    time_t setT= mktime(p);
    nowTime = time(NULL);
    printf("The difference is: %f seconds\n", difftime(setT,nowTime));
    double u = difftime(setT,nowTime);
    return u;
}
void seconds_sleep(unsigned long seconds)
{
        struct timeval tv;
        tv.tv_sec = seconds;
        tv.tv_usec = 0;
        int err;
        do{
          err = select(0,NULL,NULL,NULL,&tv);
        }while(err<0 && errno==EINTR);
}

THFNRETURN STDCALL ThreadFunc2(void* pParam)
{
    while(1)
    {
        //    mutex.ThreadLock();
        for(int i = 0;i<3;i++)
        {
            double divtime = get_div_seconds(TimeBuf[i][0],TimeBuf[i][1]);
            if(divtime<0)
            {
                continue;
            }
            cout<<"div_"<<i+1<<":sleep "<<divtime<<"s"<<(divtime/60)<<"mins,and then sem_post"<<endl;
            divNow = i;
            seconds_sleep(divtime);
            sem_post(&bin_sem);
            cout<<"already post sem"<<endl;
        }
    }
}

void create_dConfig_table()
{
    try
    {
        db.open(gszFile);
        if((!db.tableExists("PhaseConfigTable")) || (!db.tableExists("plan1")) || (!db.tableExists("dConfig")))    
        {
            //Config.db  初次建默认表
            db.execDML("create table PhaseConfigTable(phase_id int,GreenShackTime int,YellowTime int,bindChannel1 int,bindChannel2 int);");
            db.execDML("create table plan1(phase_id int, GreenTime int,phase_sequence int);");
            db.execDML("create table plan2(phase_id int, GreenTime int,phase_sequence int);");
            db.execDML("create table plan3(phase_id int, GreenTime int,phase_sequence int);");
            db.execDML("create table dConfig(timeDivHour int,timeDivMins int, planNub int);");
            //插入默认数据
            db.execDML("insert into PhaseConfigTable values (1,3,2,1,3);");
            db.execDML("insert into PhaseConfigTable values (2,3,2,2,4);");
            db.execDML("insert into PhaseConfigTable values (3,3,2,5,7);");
            db.execDML("insert into PhaseConfigTable values (4,3,2,6,8);");
            /* cout << nRows << " rows inserted" << endl; */
            db.execDML("insert into plan1 values (1,10,1);");
            db.execDML("insert into plan1 values (2,11,2);");
            db.execDML("insert into plan1 values (3,12,3);");
            db.execDML("insert into plan1 values (4,13,4);");
            /* cout << nRows << " rows inserted" << endl; */
            db.execDML("insert into plan2 values (1,14,1);");
            db.execDML("insert into plan2 values (2,15,2);");
            db.execDML("insert into plan2 values (3,16,3);");
            db.execDML("insert into plan2 values (4,17,4);");
            /* cout << nRows << " rows inserted" << endl; */
            db.execDML("insert into plan3 values (1,18,1);");
            db.execDML("insert into plan3 values (2,18,2);");
            db.execDML("insert into plan3 values (3,18,3);");
            db.execDML("insert into plan3 values (4,18,4);");
            /* cout << nRows << " rows inserted" << endl; */
            db.execDML("insert into dConfig values (8,30,1);");
            db.execDML("insert into dConfig values (17,0,2);");
            db.execDML("insert into dConfig values (23,59,3);");
        }
    
            try
            {
                //          取出PLAN1的值到LinkList PLhead中。
                CppSQLite3Query PLquery = db.execQuery("select * from plan1");    
                int t = 0;
                while(!PLquery.eof())
                {
                    table2[t][0]= PLquery.getIntField("GreenTime");
                    t++;
                    PLquery.nextRow();    
                }
                PLquery.finalize();    
                t = 0;
            }
        
        catch (CppSQLite3Exception& e)
        {
            cerr << e.errorCode() << ":" << e.errorMessage() <<" B1 error"<< endl;
        }
        try{

            //          取出PhaseConfigTable的值到LinkList PHhead中。
           CppSQLite3Query query = db.execQuery("select * from PhaseConfigTable"); 
           int i = 0;
            while(!query.eof())    
            {    
                /* Phase pa ;  */
                /* pa.m_phID = query.getIntField("phase_id"); */
                /* pa.m_YT = query.getIntField("YellowTime"); */
                /* YellowTimeBuf[pa.m_phID] = pa.m_YT; */
                /* pa.m_bindChannel = query.getIntField("bindChannel1"); */
                table2[i][1]= query.getIntField("YellowTime");
                table1[i][0]=query.getIntField("bindChannel1");
                table1[i][1]=query.getIntField("bindChannel2");
                printf("read [ %d ]:table1 %d,%d ,table2 %d,%d\n",i,table1[i][0],table1[i][1],table2[i][0],table2[i][1]);
                i++;
               // PHhead.Insert(pa,ph);
                query.nextRow();    
            }    
            query.finalize(); 
            i = 0;
            
        }
        catch (CppSQLite3Exception& e)
        {
            cerr << e.errorCode() << ":" << e.errorMessage() <<" B2 error"<< endl;
        }
        try{
            //          取出dConfig的值到LinkList DPhead中。
            CppSQLite3Query DPquery = db.execQuery("select * from dConfig");    
            int dp = 0;
            while(!DPquery.eof())    
            {    
                /* DP Dconfig;  */
                //  Dconfig.m_dpID = query.getIntField("phase_id");
                /* Dconfig.m_DivTime = DPquery.getIntField("timeDivHour"); */
                /* Dconfig.m_plID = DPquery.getIntField("planNub"); */
    //          DPhead.Insert(Dconfig,dp);
                TimeBuf[dp][0] = DPquery.getIntField("timeDivHour");
                TimeBuf[dp][1] = DPquery.getIntField("timeDivMins");
                printf("[ %d ] Timetable %d,%d\n",dp,TimeBuf[dp][0],TimeBuf[dp][1]);
                dp++;
                DPquery.nextRow();    
            }    
            DPquery.finalize();    
        }
        catch (CppSQLite3Exception& e)
        {
            cerr << e.errorCode() << ":" << e.errorMessage() <<" B3 error"<< endl;
        }
    db.close();    
    //           system("pause");  
}
catch (CppSQLite3Exception& e)
{
    cerr << e.errorCode() << ":" << e.errorMessage() << endl;
}
}

/*
void init_dConfig_linklist()
{
    for(int i=0;i<4;i++)
    {
    val1.id = i+1,
    val1.dTimeG = GreenTimeBuf[i],    
    val1.dTimeY = YellowTimeBuf[i];
    val1.dTime = val1.dTimeG +val1.dTimeY;
    head.Insert(val1,i);  
    
    }
    cout<<"Insert test:"<<endl;  
}
*/

bool set_light()
{
    
    int k = 0;
    int t = 0;
    int sT = 0;
    int color =0;
while(1)
{

    for(int u=0;u<4;u++)
    {
        for(int v=0;v<2;v++)
        {
            data.d = 0;//清空
            printf("Time_table2:[%d],[%d]:%d\n",u,v,table2[u][v]);
            sT = table2[u][v];
            for(int q=0;q<2;q++)
            {
                t = table1[u][q];
                printf("Phase_table1:[%d],[%d]:%d\n",u,q,table1[u][q]);
                if(v == 0)//绿灯
                {
                    data.d |= (1<<(3*t-3));//置绿
                }
                else//黄灯
                {
                    data.d |= (1<<(3*t-1));//置黄
                }    
            }
            while(sT != 0)
            {
                for(int i=0;i<8;i++)
                {
                    k = ChannelIDbuf[i];
                    if(!((data.d>>(3*k-3))&0x1) || (!(data.d>>(3*k-1))&0x1))//不为 绿 或 黄的通道
                    {
                        data.d |= (1<<(3*k-2));//置红
                    }
                    if(((data.d>>(3*k-3))&0x1))//绿
                    {
                        color = 42;
                    }
                    else if(((data.d>>(3*k-1))&0x1))//黄
                    {
                        color = 43;
                    }
                    else
                    {
                        color = 41;
                    }
                    printf("\033[%d;34m [ %d ] lightID .%ds]\033[5m",color,i+1,sT);
                    printf("\n");
                }
                    printf("\n");

                sleep(1);
                sT--;
            }
            printf("\n");
        }
    }
}
}

int main (int argc,char* argv[])
{
    create_dConfig_table();
//    canInit();
    /* init_dConfig_linklist(); */
    int res = sem_init(&bin_sem, 0, 0);  
    if (res != 0)  
    {  
         perror("Semaphore initialization failed");  
    }  
    cout<<"sem_init"<<endl;  

    ALLOSThread* pThread = new ALLOSThread;
    if(pThread != NULL)
    {
        pThread->CreateThread(ThreadFunc1,NULL);
        pThread->CreateThread(ThreadFunc2,NULL);
    }
    else
    {
        delete pThread;
    }
    set_light();
}

