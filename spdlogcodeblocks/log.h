#ifndef LOG_H_INCLUDED
#define LOG_H_INCLUDED



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

#include "../spdtest/include/spdlog/spdlog.h"
#include "../spdtest/include/spdlog/sinks/msvc_sink.h"

#define TRACE hik::log::trace
#define DEBUG hik::log::debug
#define INFO  hik::log::info
#define WARN  hik::log::warn
#define ERR   hik::log::error
#define FATAL hik::log::fatal


#define FAULT_LOG_FILE		"./faultlog.dat"
#define FAULT_LOG_MAX_SIZE	262144	//256k
#define FAULT_LOG_MAX_NUM	(FAULT_LOG_MAX_SIZE / sizeof(FaultLogInfo)
#define MSGSIZE (sizeof(struct msgbuf) - sizeof(long))
#define MSG_FAULT_LOG   3
#define READ_FAULT_LOG	1
#define WRITE_FAULT_LOG	2
#define CLEAR_FAULT_LOG	3
/* #pragma comment(lib,"pthreadVC2.lib")  */

namespace hik
{
    static int msgid = -1;
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
		unsigned int nType;	//故障类型ID,对应于枚举FaultLogType
		unsigned int nTime;	//故障发生时间
		unsigned int nValue;	//故障附带值
	}FaultLogInfo ;

	typedef struct faultLogHead
	{
		unsigned int num;
		FaultLogInfo data[0];
	} FaultLogHead;

	struct msgbuf
	{
		unsigned int msgflag;
		unsigned int nNumber;	//序列号
		unsigned int nType;	//故障类型ID,对应于枚举FaultLogType
		unsigned int nTime;	//故障发生时间
		unsigned int nValue;	//故障附带值
    };

	void *FaultLogModule(void *arg)
	{
		struct msgbuf msg;
		/* struct FaultLogInfo msg; */
        int fd = open(FAULT_LOG_FILE, O_RDWR | O_APPEND | O_CREAT, 0666);
		int totalsize = sizeof(FaultLogHead) + FAULT_LOG_MAX_SIZE;
		FaultLogHead tmp, *head = NULL;
		FaultLogInfo *info = NULL;

		if (fd == -1)
		{
			/* log_error("open %s fail, error info: %s", FAULT_LOG_FILE, strerror(errno)); */
//			ERR("open {} fail, error info: {}", FAULT_LOG_FILE, strerror(errno));
			pthread_exit(NULL);
		}

		tmp.num = 0;
		read(fd, &tmp, sizeof(tmp));
		if (tmp.num == 0)
		{
			ftruncate(fd, totalsize);
        }
		else
		{
			/* INFO("the number of fault log is %d", tmp.num); */
//			INFO("the number of fault log is {}", tmp.num);
		}
		head = (FaultLogHead *)mmap(NULL, totalsize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
		if (head == MAP_FAILED)
		{
			/* log_error("mmap %s fail, error info: %s", FAULT_LOG_FILE, strerror(errno)); */
//			ERR("mmap {} fail, error info: {}",FAULT_LOG_FILE, strerror(errno));
			close(fd);
			pthread_exit(NULL);
		}
		head->num = tmp.num;
		memset(&msg, 0, sizeof(msg));
		while (1)
		{
			if (-1 == msgrcv(msgid, &msg, MSGSIZE, MSG_FAULT_LOG, 0))
			{
				usleep(100000);
				continue;
			}
			if (msg.msgflag == WRITE_FAULT_LOG)
			{

				if (head->num+ 1 > FAULT_LOG_MAX_NUM)
				)					{head->num = 0;	}//写到文件末尾了重头覆盖
				info = head->data + head->num;
				info->nNumber = head->num + 1;
				info->nType = msg.nType;
				info->nTime = msg.nTime;
				info->nValue = msg.nValue;
				head->num++;
				msync(info, sizeof(FaultLogInfo), MS_ASYNC);//内存与文件同步
				msync(head, sizeof(head->num), MS_ASYNC);
			}
			else if (msg.msgflag == READ_FAULT_LOG)
            {
				/* UploadFaultLogDeal(&msg, head); */
			}
			else if (msg.msgflag == CLEAR_FAULT_LOG)
			{
				memset(head, 0, totalsize);
			}
		}
	}

	void ItsWriteFaultLog(unsigned int type,unsigned int value)//(FaultLogType type, int value)
	{
		struct msgbuf msg;
		msg.msgflag = WRITE_FAULT_LOG;
		msg.nType = type;
		msg.nTime = time(NULL);
		msg.nValue = value;
		if (msgsnd(msgid, &msg, MSGSIZE, IPC_NOWAIT) != 0)
		{
//				log_error("send write fault log msg fail, errno info: %s", strerror(errno));
//            ERR("send write fault log msg fail, errno info: {}", strerror(errno));
		}
	}
std::vector<FaultLogInfo> ItsReadFaultLog(const time_t startTM, const time_t endTM)
{

    std::int n[4];
    std::long size;
    std::ifstream infile(FAULT_LOG_FILE, ios::in|ios::binary|ios::ate);
    if(!infile.is_open())
    {
 //       cerr << "error:unable to open input file:" << infile << endl;
 //       return -1;
    }
    size = infile.tellg();
    infile.seekg (0, ios::beg);
    while(!infile.eof())
    {
      infile.read((unsigned char*)n,sizeof(n));
      infile.seekp(16,ios::cur);
    }

    FaultLogInfo get;
    get.nTime = n
    std::vector<FaultLogInfo> rlt;
//    rlt.push(get);

/*
	struct msgbuf msg;
	FaultLogInfo zero;	//表明上载故障日志出错，默认应答回复1个空的故障日志

	if (netArg == NULL || func == NULL)
		return;
	if (netArgSize > MSGSIZE - sizeof(struct faultLogMsg))
	{
		ERR("network arguments size exceed msg space");
		memset(&zero, 0, sizeof(FaultLogInfo));
		func(netArg, &zero, sizeof(FaultLogInfo));
	}
	else
	{
		memset(&msg, 0, sizeof(msg));
		msg.mtype = MSG_FAULT_LOG;
		msg.msgFLrwflag = READ_FAULT_LOG;
		msg.msgFLstartLine = startLine;
		msg.msgFLlineNum = lineNum;
		msg.msgFLfunc = func;
		memcpy(msg.msgFLnetArg, netArg, netArgSize);
		if (msgsnd(msgid, &msg, MSGSIZE, IPC_NOWAIT) != 0)
			log_error("send read fault log msg fail, errno info: %s", strerror(errno));
	}
*/
}

	class errorLog
	{
		public:
		errorLog()
		{
			pthread_t errorLog_pid;
			if (pthread_create(&errorLog_pid, NULL, FaultLogModule, NULL) == -1)
			{
				/* log_error("create %s module fail, error info:%s\n", info->moduleName, strerror(errno)); */
//				ERR("create module fail, error info:{}", /*info->moduleName, */strerror(errno));
				exit(1);
			}
			pthread_detach(0);

		}

		/* void write(event_enum eventkey, const int value); */

		//std::vector<FaultLog> read(const time_t start, const time_t end);
		//string read(const time_t start, const time_t end);//查询指定日期范围内的小日志记录.
	};

	class log
	{
	public:
		log()
		{
            //file_logger = spdlog::rotating_logger_mt("file_logger", "small_log", 1048576 * 5, 3);
            file_logger = spdlog::daily_logger_mt("file_logger", "daily", 0, 1);
            file_logger->info("this is start");
		}

    /*
    void initlog()
    {
        //file_logger = spdlog::rotating_logger_mt("file_logger", "small_log", 1048576 * 5, 3);
        file_logger = spdlog::daily_logger_mt("daily_logger", "daily", 0, 1);
		file_logger->info("this is start");
    }
    */
		template < typename... Args>
		static void trace(const std::string& module, const char* fmt, Args&&... args)
		{
			file_logger->trace(fmt,args...);
		}
		template < typename... Args>
		static void debug(const std::string& module, const char* fmt, Args&&... args)
		{
			file_logger->debug(fmt,args...);
		}
		template < typename... Args>
		static void info(const std::string& module, const char* fmt, Args&&... args)
        {
			file_logger->info(fmt,args...);
		}
		template < typename... Args>
		static void warn(const std::string& module, const char* fmt, Args&&... args)
		{
            file_logger->warn(fmt,args...);
		}
		template < typename... Args>
		static void error(const std::string& module, const char* fmt, Args&&... args)
		{
            file_logger->error(fmt,args...);
		}
		template< typename... Args>
		static void fatal(const std::string& module, const char* fmt, Args&&... args)
        {
            file_logger->critical(fmt,args...);
		}
		static std::shared_ptr<spdlog::logger> file_logger;
    private:
        std::string _base_filename;
        std::size_t _max_size;
        std::size_t _max_files;
        std::size_t _current_size;
		std::string _pattern = "[ %Y-%m-%d %H:%M:%S.%e %l ]";


	};
		 std::shared_ptr<spdlog::logger> log::file_logger;

}



#endif // LOG_H_INCLUDED
