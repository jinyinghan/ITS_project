#ifndef __SCLOG_H__
#define __SCLOG_H__

#include <string>
#include <vector>
#include "include/spdlog/spdlog.h"

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
typedef struct FaultLog
{
	unsigned int seq;	//序列号
	unsigned int type;	//故障类型
	unsigned int time;	//故障发生时间
	unsigned int value;	//故障附带值
};

using namespace std;
class log 
{
public:
	log();
	log(const std::string& logger_name);
	log(const size_t max_file_size);
	log(const size_t max_file_size, const size_t max_files);

	template < typename... Args>
	void trace(module_enum module, const char* fmt, Args&&... args);
	template<typename T>
	void trace(module_enum module, const T& msg);

	template < typename... Args>
	void debug(module_enum module, const char* fmt, Args&&... args);
	template<typename T>
	void debug(module_enum module, const T& msg);

	template < typename... Args>
	void info(module_enum module, const char* fmt, Args&&... args);
	template<typename T>
	void info(module_enum module, const T& msg);

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

	vector<FaultLog> read(const time_t start, const time_t end);
	//	string read(const time_t start, const time_t end);//查询指定日期范围内的小日志记录.
	static std::shared_ptr<spdlog::logger> file_logger;
	string logger_name;
private:
	string _filename = "";
	string _pattern = "[ %Y-%m-%d %H:%M:%S.%e %l ]";
	string _level = "off";
	size_t _max_file_size = 1024 * 1024 * 1;
	size_t _max_files = 7;

};

#endif //__SCLOG_H__
