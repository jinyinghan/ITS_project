#include "sclog.h"

//using namespace std;
namespace hik
{


	log::log()
	{
		file_logger = spdlog::rotating_logger_mt("file_logger", _filename, _max_file_size, _max_files);
	}
	log::log(const std::string& logger_name)
	{
		if (file_logger)
		{
			file_logger = nullptr;
		}
		try
		{
			std::vector<spdlog::sink_ptr> sinks;
			sinks.push_back(std::make_shared<spdlog::sinks::msvc_sink_mt>());
			sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>(_filename, _max_file_size, 1));
			file_logger = std::make_shared<spdlog::logger>(_filename, begin(sinks), end(sinks));
			file_logger->set_pattern("[%Y-%m-%d %H:%M:%S] %v");
			file_logger->set_level(spdlog::level::trace);
			file_logger->info("======== init_log ========");
		}

		catch (...)
		{
			file_logger = nullptr;
		}
		//	 file_logger = spdlog::rotating_logger_mt("file_logger", _filename, _max_file_size, _max_files);
	}
	log::log(const size_t max_file_size) :_max_file_size(max_file_size)
	{
		file_logger = spdlog::rotating_logger_mt("file_logger", _filename, _max_file_size, _max_files);
	}

	void log::init_log()
	{
		file_logger = spdlog::rotating_logger_mt("file_logger", _filename, _max_file_size, _max_files);
	}
//	template < typename... Args>
//	static inline void log::fortest(std::string module, const char* fmt, Args&&... args)
//	{
//		file_logger->spdlog::logger::info(fmt, args...);
//	}

//	template<typename T>
	//inline void log::info(std::string& module, const T& msg)
	//{
	//	file_logger->spdlog::info(msg);
	//}



/*	void errLog::init_errLog()
	{
		if (_errLogger) _errLogger = nullptr;
		try
		{
			std::vector<spdlog::sink_ptr> sinks;
			sinks.push_back(std::make_shared<spdlog::sinks::msvc_sink_mt>());
//			sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>(file_name, 1024 * 1024 * 4, 1));
//			_errLogger = std::make_shared<spdlog::logger>(file_name, begin(sinks), end(sinks));
//			_errLogger->set_pattern("[%Y-%m-%d %H:%M:%S] %v");
//		    combined_logger->set_level(spdlog::level::trace);
//			_errLogger->info("======== init_log ========");
		}
		catch (...)
		{
//			_errLogger = nullptr;
		}
	}
	*/
//	/*inline*/ void errLog::write(unsigned int type, unsigned int value)
	//{
	//	char* u = "hh";
//		if (_errLogger) _errLogger->info(u,type, value);
	//}












	/*
	class errLog
	{
	public:
	errLog() = delete;
	static std::shared_ptr<spdlog::logger> _errLogger;
	/*
	static void init_errLog()
	{
	auto _errLogger1 = spdlog::rotating_logger_mt("file_logger", "errLog", 1048576 * 5, 3);
	}
	*/
	/*
	if (_errLogger) _errLogger = nullptr;
	try
	{
	_errLogger = spdlog::rotating_logger_mt("file_logger", "errLog", 1048576 * 5, 3);
	}
	catch (...)
	{
	_errLogger = nullptr;
	}

	}
	static  void write(unsigned int type, unsigned int value)//小日志的记录写入方法.
	{
	if (_errLogger) _errLogger->info("{},{}", type, value);
	}
	static std::vector<FaultLog> read(const time_t start, const time_t end)
	{
	FaultLog get;

	std::vector<FaultLog> rlt;
	rlt.push_back(get);
	}
	static void flush()
	{
	if (_errLogger) _errLogger->flush();
	}

	static void release_log()
	{
	flush();
	_errLogger = nullptr;
	}
	//	static const size_t _max_file_size = 1024 * 1024 * 1;
	//	static const std::string _filename = "errlog";
	//
	};
	std::shared_ptr<spdlog::logger> errLog::_errLogger;

	std::vector<FaultLog> read(const time_t start, const time_t end)
	{
	std::string str;
	std::ifstream infile("eeeerrorlog");
	while (!infile.eof())
	{
	getline(infile, str);
	//		strstr(str.c_str(), "start")


	}
	/*	FaultLog get;
	std::vector<FaultLog> rlt;
	get.seq = ;
	get.time = ;
	get.type = ;
	get.value = ;
	rlt.push_back(get);
	std::vector<FaultLog>::iterator iter;
	std::vector<FaultLog>::iterator
	start = rlt.begin();
	for (iter = rlt.begin(); iter != rlt.end(); iter++)
	{
	}

	}
	*/


}