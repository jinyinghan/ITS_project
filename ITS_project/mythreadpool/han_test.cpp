/**********************************************
*Project:ThreadPool for ITS
*
*Author:GenieHan
*email:976424706.com
*
***********************************************/

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "han_ThreadPool.h"

using namespace std;
class Mytask : public ITS::Task
{
    public:
        Mytask()
        {
        }
        virtual int run()
        {
            printf("thread[%lu] : %s\n",pthread_self(),(char*) this->arg_);
            sleep(1);
            return 0;
        }
};

int main()
{
    cout << "begin" << endl;
    char szTmp[] = "this is my ITS threadpool test";
    Mytask taskobj;
    taskobj.setArg((void*)szTmp);
    
    ITS::ThreadPool threadPool(10); 
    threadPool.start();

    for(int i = 0; i < 20;i++)
    {
        threadPool.addTask(&taskobj);
    }

    while(1)
    {
        printf("there are still %d tasks need to process\n",threadPool.size());
        if(threadPool.size() == 0)
        {
            threadPool.stop();
            printf("now I will exit from main\n");
            exit(0);
        }
        sleep(2);
    }
    cout << "end" << endl;
    return 0;
}
