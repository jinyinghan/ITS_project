#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <pthread.h>
#include <ncurses.h>
#include "capsulation_thread.h"
#include "ring_queue.h"
#define DATA_TYPE int
const int LOOP_SIZE = 1024;

void* logic_run(void* arg)
{

}
class Logic_Execute : public Thread
{
    public:
        Logic_Execute()
        {
            loop_ = true;
        }

        virtual void run()
        {
            Ring_Queue queueExc = *(Ring_Queue*)arg;
            while(loop_)
            {
                for(int i = 0;i < LOOP_SIZE;)
                {
                    int *p = 0;
                    p =                      (DATA_TYPE*)queueExc.ReadQ();
                    if (p)
                    {
                        assert(i == *p);
                        printf("[%d]:[%d]\n",i,*p);
                        queueExc.Read_Over();
                        i++;
                    }
                }
            }
            printf("Logic_Execute exit:loop down\n");
        }
    private:
        bool loop_;
};

class Lets_Config : public Thread
{
    public:
        Lets_Config()
        {
            loop_ = true;
        }

        virtual void run()
        {
            Ring_Queue queueCof = *(Ring_Queue*)arg;
            int loop = 0;
            struct timeval last_time,now_time;
            gettimeofday(&last_time,NULL);
            gettimeofday(&now_time,NULL);
            while(loop_)
            {
                for(int i = 0;i < LOOP_SIZE;)
                {
                    int *p = 0;
                    p =                      (DATA_TYPE*)queueCof.WriteQ();
                    if (p)
                    {
                        *p =i;
                        printf("[%d]:[%d]\n",i,*p);
                        queueCof.Write_Over();
                        i++;
                    }
                }
                gettimeofday(&now_time,NULL);
                if (now_time.tv_sec - last_time.tv_sec >= 5)
                {
                    printf("LOOP_COUNT is %.2f=[ %d[RING_SIZE] * %.2f[RING_COUNT]] per second\n",(LOOP_SIZE*loop)/5.0,LOOP_SIZE,loop/5.0);
                    last_time = now_time;
                    loop = 0;
                }
                loop++;
            }
            printf("Lets_config exit:loop down\n");
        }
    private:
        bool loop_;
};

