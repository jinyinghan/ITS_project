#ifndef __SCLOG1_H__
#define __SCLOG1_H__

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

#include "./include/spdlog/spdlog.h"
#include "./include/spdlog/sinks/msvc_sink.h"

#define FAULT_LOG_FILE		"/home/faultlog.dat"
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
		int num;
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
		printf("open /home/faultlog\n");
        int totalsize = sizeof(FaultLogHead) + FAULT_LOG_MAX_SIZE;
		FaultLogHead tmp, *head = NULL;
		FaultLogInfo *info = NULL;

		if (fd == -1)
		{
			/* log_error("open %s fail, error info: %s", FAULT_LOG_FILE, strerror(errno)); */
			printf("open /home/faultlog fail\n");
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
		}
		head = (FaultLogHead *)mmap(NULL, totalsize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
		if (head == MAP_FAILED)
		{
			/* log_error("mmap %s fail, error info: %s", FAULT_LOG_FILE, strerror(errno)); */
			close(fd);
			pthread_exit(NULL);
		}
		head->num = tmp.num;
		memset(&msg, 0, sizeof(msg));
		while (1)
		{
			if (-1 == msgrcv(msgid, &msg, MSGSIZE, MSG_FAULT_LOG, 0))
			{
				usleep(1000);
				continue;
			}
			if (msg.msgflag == WRITE_FAULT_LOG)
			{
				if (head->num+ 1 > FAULT_LOG_MAX_NUM)
                    )	{head->num = 0;	}//写到文件末尾了重头覆盖
				info = head->data + head->num;
				info->nNumber = head->num + 1;
				info->nType = msg.nType;
				info->nTime = msg.nTime;
				info->nValue = msg.nValue;
				head->num++;
				msync(info, sizeof(FaultLogInfo), MS_ASYNC);
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
		}
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
		file_logger = spdlog::daily_logger_mt("daily_logger", "daily", 0, 1);
		}
		template < typename... Args>
		static void trace(const std::string& module, const char* fmt, Args&&... args)
		{
			file_logger->trace(fmt,args...);
		}
		template < typename... Args>
		void debug(const std::string& module, const char* fmt, Args&&... args);

		template < typename... Args>
		void info(const std::string& module, const char* fmt, Args&&... args);

		template < typename... Args>
		void warn(const std::string& module, const char* fmt, Args&&... args);

		template < typename... Args>
		void error(const std::string& module, const char* fmt, Args&&... args);

		template< typename... Args>
		void fatal(const std::string& module, const char* fmt, Args&&... args);

		static std::shared_ptr<spdlog::logger> file_logger;
		std::string _pattern = "[ %Y-%m-%d %H:%M:%S.%e %l ]";
		size_t _max_file_size = 1024 * 1024 * 1;
		size_t _max_files = 1;

	};
		 std::shared_ptr<spdlog::logger> log::file_logger;

}
#endif //__SCLOG1_H__
