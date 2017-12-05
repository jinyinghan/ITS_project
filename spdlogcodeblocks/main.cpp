
#include "log.h"

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
        string s = "hi,diss";
		TRACE("hurry","thread [{}] : {}",pthread_self(),(char*) this->arg_);
		DEBUG("hurry","thread [{}] : {}",pthread_self(),(char*) this->arg_);
		INFO("hurry","thread [{}] : {}",pthread_self(),(char*) this->arg_);
		WARN("hurry","thread [{}] : {}",pthread_self(),(char*) this->arg_);
		ERR("hurry","thread [{}] : {}",pthread_self(),(char*) this->arg_);
		FATAL("hurry","thread{} : {}",pthread_self(),(char*) this->arg_);
		hik::ItsWriteFaultLog(1,2);

            sleep(1);
            return 0;
        }
};
int main()
{

cout<<"coming..."<<endl;
    hik::errorLog log1;

    hik::log log2;
//    log2.initlog();
    int i=0;
    string s = "hi,diss";
    char szTmp[] = "this is my ITS threadpool test";
	for(i=0;i<10;i++)
	{
		TRACE("hurry","{}",s);
		DEBUG("hurry","{}",s);
		INFO("hurry","{}",s);
		WARN("hurry","{}",s);
		ERR("hurry","{}",s);
		FATAL("hurry","{}",s);

	}

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
