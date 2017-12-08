#include <stdio.h>
#include <time.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
typedef struct
{
    unsigned int seq;
    unsigned int nTime;
    unsigned int key;
    unsigned int value;
}FaultLogInfo;

int main()
{
    int fd,i;
    FaultLogInfo *p_head;
    fd = open("./testmmap.txt",O_CREAT|O_RDWR|O_TRUNC,00777);
    lseek(fd,sizeof(FaultLogInfo)*5-1,SEEK_SET);
    write(fd,"",1);
    p_head = (FaultLogInfo*)mmap(NULL,sizeof(FaultLogInfo)*10,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    close(fd);
    for(i=0;i <10;i++)
    {
        (*(p_head+i)).seq = i+1;
        (*(p_head+i)).nTime = time(NULL);
        (*(p_head+i)).key = i*1;
        (*(p_head+i)).value = i*2;
        usleep(1300);
    }
    printf("initializeover\n");
    sleep(10);
    munmap(p_head,sizeof(FaultLogInfo)*10);
    printf("umapok\n");
    return 0;
}
