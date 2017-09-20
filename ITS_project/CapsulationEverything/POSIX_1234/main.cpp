
#include "Thread.h"
#include "MutexLock.h"
#include "Condition.h"
#include  <vector>
#include <memory>
using namespace std;
MutexLock mutex;//互斥锁
Condition cond(mutex);//条件变量
int count =0;
class IncCount : public Thread
{
    private:
        int id_;
    public:
        IncCount(int id):id_(id){}
        void run()
        {
            for(int i=0;i < 10;i ++)
            {
                {
                    MutexLockGuard lock(mutex);
                    count++;
                    if (count == 12)
                    {
                        cond.notify();
                    }
                    std::cout<<"thread : "<<id_<<" count : "<< count << std::endl;
                }
                sleep(1.5);
            }
        }
};
class WatchCount: public Thread
{
    private:
        int id_;
    public:
        WatchCount(int id):id_(id){}


        void run()
        {
            MutexLockGuard lock(mutex);
            while(count < 12)
            {
                cond.wait();
            }
            assert(count>=12);
            count+=125;
            std::cout<<"thread : "<<id_<<" count : "<< count << std::endl;
        }
};

int main()
{
    {
        vector< shared_ptr<Thread> > t(3);

        t[0].reset(new WatchCount(1));
        t[1].reset(new IncCount(2));
        t[2].reset(new IncCount(3));
        for(int i=0;i<3;i++)
        {
            t[i]->start();
        }
        for(int i=0;i<3;i++)
        {
            t[i]->join();
        }

    }
    return 0;
}