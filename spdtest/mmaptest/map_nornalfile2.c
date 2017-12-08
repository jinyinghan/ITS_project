#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <vector>
#include <time.h>
using namespace std;
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
   FaultLogInfo get;
   vector<FaultLogInfo> rlt;
   int startTM = time(NULL);
    printf("startTM = %d\n",startTM);
   fd = open("./testmmap.txt",O_CREAT|O_RDWR,00777);
   p_head = (FaultLogInfo*)mmap(NULL,sizeof(FaultLogInfo)*10,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
   for(i=0;i<10;i++)
   {
       printf("seq:%d,nTime:%d,key:%d,value:%d\n",(*(p_head+i)).seq,(*(p_head+i)).nTime,(*(p_head+i)).key,(*(p_head+i)).value);
        if(((*(p_head+i)).nTime) <= startTM)
        {        
        get.seq = (*(p_head+i)).seq ;
        get.nTime = (*(p_head+i)).nTime ;
        get.key = (*(p_head+i)).key ;
        get.value = (*(p_head+i)).value ;
       printf("push [[ seq:%d,nTime:%d,key:%d,value:%d ]]\n",(*(p_head+i)).seq,(*(p_head+i)).nTime,(*(p_head+i)).key,(*(p_head+i)).value);
        rlt.push_back(get);
        }
   }
    munmap(p_head,sizeof(FaultLogInfo)*10);
    return 0;
}
