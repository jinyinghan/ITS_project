#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

enum weekday{sun=7,mon=1,tue,wed,thu,fri,sat}day;
enum direction{ews,ewt,nss,nst}now;
int setTicker(int);
void show();

int main()
{
    setTicker(200);
    while(1)
    {
        /* signal(SIGALRM, show); */

    }
}


void show()
{
    for(int i=0;i<4;i++)
    {
        now = (enum direction)i;
        switch(now)
        {
            case ews:
                printf("ews\v");
            break;
            case ewt:
                printf("ewt\v");
            break;
            case nss:
                printf("nss\v");
            break;
            case nst:
                printf("nst\v");
            break;
            default:
            printf("wahahaha crush!!!\n");
        }
    }
}

int setTicker(int n_msecs)
{
    struct itimerval new_timeset;
    long    n_sec, n_usecs;

    n_sec = n_msecs / 1000 ;
    n_usecs = ( n_msecs % 1000 ) * 1000L ;
    new_timeset.it_interval.tv_sec  = n_sec;        
    new_timeset.it_interval.tv_usec = n_usecs;      
    n_msecs = 1;
    n_sec = n_msecs / 1000 ;
    n_usecs = ( n_msecs % 1000 ) * 1000L ;
    new_timeset.it_value.tv_sec     = n_sec  ;      
    new_timeset.it_value.tv_usec    = n_usecs ;     
    return setitimer(ITIMER_REAL, &new_timeset, NULL);
}
