
#include "log.h"

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

using namespace std;


void* thdo(void* args)
{
    for (int i = 0;i < 1e7; ++i)
    {
        TRACE("hurry","thread [{}] : {}", i ,"hello");
		DEBUG("hurry","thread [{}] : {}", i ,"hello");
		INFO("hurry","thread [{}] : {}", i ,"hello");
		WARN("hurry","thread [{}] : {}", i ,"hello");
		ERR("hurry","thread [{}] : {}", i ,"hello");
		FATAL("hurry","thread{} : {}", i ,"hello");
    	sleep(1);
	}
    return 0;
}

int main(int argc, char** argv)
{
    hik::log log;
    hik::errorLog log2;

    pthread_t tids[5];
    for (int i = 0;i < 5; ++i)
    	pthread_create(&tids[i], NULL, thdo, NULL);

    for (int i = 0;i < 5; ++i)
	pthread_join(tids[i], NULL);

}
