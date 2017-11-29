#ifndef __SCLOG_H__
#define __SCLOG_H__

#include <string>
#include <vector>
#include "include/spdlog/spdlog.h"
#include "include/spdlog/sinks/msvc_sink.h"
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
#include <pthread.h>
//#ifdef __linux__
//#include <sys/socket.h>
//#include <sys/mman.h>
//#include <unistd.h>
//#endif
#ifdef __windows__
#include <windows.h>
#endif
#define FAULT_LOG_FILE		"/home/faultlog.dat"
#define FAULT_LOG_MAX_SIZE	262144	//256k
#define FAULT_LOG_MAX_NUM	(FAULT_LOG_MAX_SIZE / sizeof(FaultLogInfo)
#define READ_FAULT_LOG	1
#define WRITE_FAULT_LOG	2
#define CLEAR_FAULT_LOG	3
#pragma comment(lib,"pthreadVC2.lib") 
namespace hik
{
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
	typedef enum
	{
		module1 = 0,
		module2 = 1,
		module3 = 2,
		module4 = 3,
		module5 = 4,
		module6 = 5,
		module7 = 6
	} module_enum;
	typedef enum
	{
		event1 = 0,
		event2 = 1,
		event3 = 2,
		event4 = 3,
		event5 = 4,
	} event_enum;
	typedef struct _fault_log_info
	{
		unsigned int nNumber;	//序列号
		unsigned int nID;	//故障类型ID,对应于枚举FaultLogType
		unsigned int nTime;	//故障发生时间
		unsigned int nValue;	//故障附带值
	}FaultLogInfo ;
	typedef struct faultLogHead
	{
		int num;
		FaultLogInfo data[0];
	} FaultLogHead;


	void *FaultLogModule(void *arg)
	{
		struct msgbuf msg;
		int fd = open(FAULT_LOG_FILE, O_RDWR | O_APPEND | O_CREAT, 0666);
		int totalsize = sizeof(FaultLogHead) + FAULT_LOG_MAX_SIZE;
		FaultLogHead tmp, *head = NULL;
		FaultLogInfo *info = NULL;

		if (fd == -1)
		{
			log_error("open %s fail, error info: %s", FAULT_LOG_FILE, strerror(errno));
			pthread_exit(NULL);
		}

		tmp.num = 0;
		read(fd, &tmp, sizeof(tmp));
		if (tmp.num == 0)
			ftruncate(fd, totalsize);
		else
			INFO("the number of fault log is %d", tmp.num);
//#ifdef __linux__
		head = (FaultLogHead *)mmap(NULL, totalsize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
//#else

//		HANDLE hMapping = CreateFileMapping(fd, 0, PAGE_READONLY, 0,totalsize, "CSFlash");
	//		if (hMapping)
	//		{
	//			//以只读方式映射其中的FLASH_SIZE大小
	//			LPSTR lpData = (LPS TR)MapViewOfFile(hMapping, FILE_MAP_READ, 0, 0, FLASH_SIZE);
	//		}
//#endif
		if (head == MAP_FAILED)
		{
			log_error("mmap %s fail, error info: %s", FAULT_LOG_FILE, strerror(errno));
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
			if (msg.msgFLrwflag == WRITE_FAULT_LOG)
			{
				if (head->num + 1 > FAULT_LOG_MAX_NUM)
					head->num = 0;	//写到文件末尾了重头覆盖
				info = head->data + head->num;
				info->nNumber = head->num + 1;
				info->nID = msg.msgFLtype;
				info->nTime = msg.msgFLtime;
				info->nValue = msg.msgFLvalue;
				head->num++;
				msync(info, sizeof(FaultLogInfo), MS_ASYNC);
				msync(head, sizeof(head->num), MS_ASYNC);
			}
			else if (msg.msgFLrwflag == READ_FAULT_LOG)
				UploadFaultLogDeal(&msg, head);
			else if (msg.msgFLrwflag == CLEAR_FAULT_LOG)
				memset(head, 0, totalsize);
		}

		void ItsWriteFaultLog(unsigned int type,unsigned int value)//(FaultLogType type, int value)
		{
			struct msgbuf msg = {
				.mtype = MSG_FAULT_LOG,
				.msgText = { 0 },
			};
			msg.msgFLrwflag = WRITE_FAULT_LOG;
			msg.msgFLtype = type;
			msg.msgFLtime = time(NULL);
			msg.msgFLvalue = value;
			if (msgsnd(msgid, &msg, MSGSIZE, IPC_NOWAIT) != 0)
				log_error("send write fault log msg fail, errno info: %s", strerror(errno));
		}

	class errorLog
	{
		errorLog()
		{
			pthread_t errorLog_pid;
			if (pthread_create(errorLog_pid, NULL, FaultLogModule, NULL) == -1)
			{
				log_error("create %s module fail, error info:%s\n", info->moduleName, strerror(errno));
				exit(1);
			}
			pthread_detach(0);
			
		}

		void write(event_enum eventkey, const int value);

		//		std::vector<FaultLog> read(const time_t start, const time_t end);
		//	string read(const time_t start, const time_t end);//查询指定日期范围内的小日志记录.


	};

	class log
	{
	public:
		log();
		log(const std::string& logger_name);
		log(const size_t max_file_size);
		log(const size_t max_file_size, const size_t max_files);
		void init_log();
		template < typename... Args>
		void trace(module_enum module, const char* fmt, Args&&... args);
		template<typename T>
		void trace(module_enum module, const T& msg);

		template < typename... Args>
		void debug(module_enum module, const char* fmt, Args&&... args);
		template<typename T>
		void debug(module_enum module, const T& msg);

	//	template < typename... Args>
//	 void fortest(string& module, const char* fmt, Args&&... args);
//		template<typename T>
	//	void info(string& module, const T& msg);

		template < typename... Args>
		void warn(module_enum module, const char* fmt, Args&&... args);
		template<typename T>
		void warn(module_enum module, const T& msg);

		template < typename... Args>
		void error(module_enum module, const char* fmt, Args&&... args);
		template<typename T>
		void error(module_enum module, const T& msg);

		template< typename... Args>
		void fatal(module_enum module, const char* fmt, Args&&... args);
		template<typename T>
		void fatal(module_enum module, const T& msg);

		template<typename T>
		void write(event_enum eventkey, const int value);//小日志的记录写入方法.

//		std::vector<FaultLog> read(const time_t start, const time_t end);
		//	string read(const time_t start, const time_t end);//查询指定日期范围内的小日志记录.
		static std::shared_ptr<spdlog::logger> file_logger;
		std::string logger_name;
	private:
		std::string _filename = "Hellolog";
		std::string _pattern = "[ %Y-%m-%d %H:%M:%S.%e %l ]";
		std::string _level = "off";
		size_t _max_file_size = 1024 * 1024 * 1;
		size_t _max_files = 1;

	};

	template<const char file_name[]>
	class CLog
	{
		CLog() = delete;
		static std::shared_ptr<spdlog::logger> combined_logger;
	public:
		static void init_log()
		{
			if (combined_logger) combined_logger = nullptr;
			try
			{
				std::vector<spdlog::sink_ptr> sinks;
				sinks.push_back(std::make_shared<spdlog::sinks::msvc_sink_mt>());
				sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>(file_name, 1024 * 1024 * 4, 1));
				combined_logger = std::make_shared<spdlog::logger>(file_name, begin(sinks), end(sinks));
				combined_logger->set_pattern("[%Y-%m-%d %H:%M:%S] %v");
				//				combined_logger->set_level(spdlog::level::trace);
				combined_logger->info("======== init_log ========");
			}
			catch (...)
			{
				combined_logger = nullptr;
			}
		}

		template <typename... Args>
		static inline void log(const char* fmt, const Args&... args)
		{
			if (combined_logger) combined_logger->info(fmt, args...);
		}

		static void flush()
		{
			if (combined_logger) combined_logger->flush();
		}

		static void cease_log()
		{
			flush();
			combined_logger = nullptr;
		}
	};

	template<const char file_name[]>
	std::shared_ptr<spdlog::logger> CLog<file_name>::combined_logger = nullptr;




}
#endif //__SCLOG_H__
