#ifdef HAN_THREADPOOL_H
#define HAN_THREADPOOL_H


/**********************************************
*Project:ThreadPool for ITS
*
*Author:GenieHan
*email:976424706.com
*
***********************************************/

#include <deque>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

namespace ITS
{
    class Task 
    {
        public:
            Task(void* arg = NULL,const std::string taskName = "")
                : arg_(arg)
                , taskName_(taskName)
                {
                }
            
            virtual ~Task()
            {
            }
            
            void setArg(void* arg)
            {
                arg_ = arg;
            }
            
            virtual int run() = 0;

        protected:
            void* arg_;
            std::string taskName_;
    };

    class ThreadPool
    {
        public:
            ThreadPool(int threadNum = 10);
            ~ThreadPool();
    
            size_t addTask(Task* task);
            void    Stop();
            int     size();
            void    Start();
            Task*   take();
                            
        protected:


        private:
            int     createThreads();
            static void* threadFunc(void* threadData);
            ThreadPool& operator=(const ThreadPool&);
            ThreadPool(const ThreadPool&);

            volatile bool isRunning_;
            int threadsNum_;
            pthread_t* threads_;
            
            std::dequeue<Task*> taskQueue_;
            pthread_mutex_t mutex_;
            pthread_cond_t condition_;

    };

}
#endif // HAN_THREADPOOL_H
