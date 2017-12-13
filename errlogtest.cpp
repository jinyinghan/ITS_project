
#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <math.h>
#include <pthread.h>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/msg.h>
#include <sys/socket.h>
#include <sys/mman.h>
#include <unistd.h>
#include <vector>
#include <cstring>
//#include <iostream>
//#include <exception>


#define FAULT_LOG_FILE		"./faultlog.dat"
#define FAULT_LOG_MAX_SIZE	262144	//256k
#define FAULT_LOG_MAX_NUM	(FAULT_LOG_MAX_SIZE / sizeof(FaultLogInfo))
#define MSGSIZE (sizeof(struct msgbuf))
#define MSG_FAULT_LOG   3
#define READ_FAULT_LOG	1
#define WRITE_FAULT_LOG	2
#define CLEAR_FAULT_LOG	3
/* #pragma comment(lib,"pthreadVC2.lib")  */

namespace hik
{
    int msgid = -1;
	typedef enum
	{
		trace = 0,
		debug = 1,
		info = 2,
		warn = 3,
		err = 4,
		fatal = 5,
		//	off = 6
	} level_enum;

	typedef struct _fault_log_info
	{
		unsigned int nNumber;	//序列号
		unsigned int nTime;	    //故障发生时间
		unsigned int nType;	    //故障类型ID,对应于枚举FaultLogType
		unsigned int nValue;	//故障附带值
	}FaultLogInfo ;
	typedef struct _fault_log_head
	{
        unsigned int nowSeq;
        unsigned int refreshNub;
        unsigned int tmp1;
        unsigned int tmp2;
	}FaultLogHead;

	struct msgbuf
	{
		unsigned int msgflag;
		unsigned int nNumber;	//序列号
		unsigned int nTime;	    //故障发生时间
		unsigned int nType;	    //故障类型ID,对应于枚举FaultLogType
		unsigned int nValue;	//故障附带值
    };
class errorLog
	{

		public:
        pthread_t errorLog_pid;
        static unsigned int _nextSeq ;
        static FaultLogInfo *pMap ;
		errorLog()
		{

			if (pthread_create(&errorLog_pid, NULL, FaultLogModule, NULL) == -1)
			{
//				ERR("create module fail, error info:{}", /*info->moduleName, */strerror(errno));
printf("%d\n",__LINE__);
				exit(1);
			}
printf("%d\n",__LINE__);
			pthread_detach(0);
		}
		~errorLog()
		{
            pthread_exit(NULL);
printf("%d\n",__LINE__);
		}

        static void ItsWriteFaultLog(unsigned int type,unsigned int value)//(FaultLogType type, int value)
        {
            struct msgbuf msg;
            msg.msgflag = WRITE_FAULT_LOG;

            msg.nNumber = _nextSeq;
            msg.nTime   = time(NULL);
            msg.nType   = type;
            msg.nValue  = value;

            _nextSeq++;
            if (msgsnd(msgid, &msg, MSGSIZE, IPC_NOWAIT) != 0)
            {
            int uerr  = errno;
//          ERR("send write fault log msg fail, errno info: {}", strerror(errno));
            }
        }

        static bool ItsReadFaultLog(const time_t startTM,const time_t endTM,std::vector<hik::FaultLogInfo> &rlt)
        {
            FaultLogInfo get;
//            std::vector<FaultLogInfo> rlt;
            int startTM_tmp = time(NULL);
            printf("startTM = %d\n",startTM_tmp);
            for(int i = 1;i < FAULT_LOG_MAX_NUM;i++)
            {
 /*               if((*pMap).nNumber == 0)
                {
//                   break;
//                return false;
                }
*/
printf("%d\n",__LINE__);
                if(((*(pMap+i)).nTime) < startTM_tmp)
                {
printf("%d\n",__LINE__);
                    get.nNumber = (*(pMap+i)).nNumber ;
                    get.nTime = (*(pMap+i)).nTime ;
                    get.nType = (*(pMap+i)).nType ;
                    get.nValue = (*(pMap+i)).nValue ;
printf("%d\n",__LINE__);
                    printf("push [[ seq:%d,nTime:%d,key:%d,value:%d ]]\n",(*(pMap+i)).nNumber,(*(pMap+i)).nTime,(*(pMap+i)).nType,(*(pMap+i)).nValue);
                    rlt.push_back(get);
printf("%d\n",__LINE__);
                }
            }
            return true;
        }

    static void *FaultLogModule(void *arg)
	{
		struct msgbuf msg;

        int fd = open(FAULT_LOG_FILE, O_RDWR | O_APPEND | O_CREAT, 0666);
        FaultLogHead head;
        int mNub = 0;
		if (fd == -1)
		{
//			ERR("open {} fail, error finfo: {}", FAULT_LOG_FILE, strerror(errno));
			pthread_exit(NULL);
		}
        head.nowSeq = 0;
		read(fd, &head, sizeof(FaultLogHead));
		if (head.nowSeq == 0)
		{
			ftruncate(fd, FAULT_LOG_MAX_SIZE);
        }
        _nextSeq = head.nowSeq + 1;    //the number of fault log
printf("%d\n",__LINE__);

		pMap = (FaultLogInfo *)mmap(NULL, FAULT_LOG_MAX_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
/*		unsigned int t = 0;
		unsigned int maxseq = 0;
		for(int i = 0;i < FAULT_LOG_MAX_NUM;i++)
		{
            if((*(pMap+i)).nNumber == 0)
            {
                break;
            }
            t = (*(pMap + i)).nNumber;
            maxseq = maxseq < t? t : maxseq;
		}
        printf("the number of fault log is {%d}\n", maxseq);
        _nNumber = maxseq;
*/
		if (pMap == MAP_FAILED)
		{
//			ERR("mmap {} fail, error info: {}",FAULT_LOG_FILE, strerror(errno));
			close(fd);
			pthread_exit(NULL);
		}
        key_t key = ftok("/dev/null", 1234);
        if((msgid = msgget(key, IPC_CREAT | 0666)) == -1)
        {
            int uerrno = errno;
            exit(EXIT_FAILURE);
        }
        memset(&msg, 0, sizeof(msg));
		while (1)
		{

			if (-1 == msgrcv(msgid, &msg, MSGSIZE, MSG_FAULT_LOG, 0))
			{
				usleep(100000);//0.1s
				continue;
			}

			if (msg.msgflag == WRITE_FAULT_LOG)
			{
                head.nowSeq ++;
                head.refreshNub = _nextSeq / FAULT_LOG_MAX_NUM;
                (*pMap).nNumber = head.nowSeq;
                (*pMap).nTime = head.refreshNub;
                mNub = (_nextSeq % FAULT_LOG_MAX_NUM) + 1;

				(*(pMap+mNub)).nNumber = msg.nNumber;
                (*(pMap+mNub)).nTime = msg.nTime;
                (*(pMap+mNub)).nType = msg.nType;
                (*(pMap+mNub)).nValue = msg.nValue;
//printf("push [[ seq:%d,nTime:%d,key:%d,value:%d ]]\n",(*(pMap+mNub)).nNumber,(*(pMap+mNub)).nTime,(*(pMap+mNub)).nType,(*(pMap+mNub)).nValue);

				msync(pMap,(_nextSeq*sizeof(FaultLogInfo)), MS_ASYNC);
			}
			else if (msg.msgflag == READ_FAULT_LOG)
            {
				/* UploadFaultLogDeal(&msg, head); */
			}

		}
	}
		/* void write(event_enum eventkey, const int value); */

		//std::vector<FaultLog> read(const time_t start, const time_t end);
		//string read(const time_t start, const time_t end);//查询指定日期范围内的小日志记录.


	};
	 unsigned int errorLog::_nextSeq;
	 FaultLogInfo * errorLog::pMap;

}

int main()
{

std::cout<<"coming..."<<std::endl;
    hik::errorLog log1;
std::vector <hik::FaultLogInfo> vecTemp;
    time_t walla = time(NULL);
bool res = hik::errorLog::ItsReadFaultLog(walla,walla,vecTemp);
while(1)
{
for(int i =0;i<10;i++)
{
hik::errorLog::ItsWriteFaultLog(1,i);
}
res = hik::errorLog::ItsReadFaultLog(walla,walla,vecTemp);
}
//	hik::errorLog::ItsWriteFaultLog(1,2);
//    std::vector <hik::FaultLogInfo> vecTemp;
//    time_t walla = time(NULL);
//bool res = hik::errorLog::ItsReadFaultLog(walla,walla,vecTemp);


}

