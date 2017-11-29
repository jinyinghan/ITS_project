
// testSPD.cpp : 定义控制台应用程序的入口点。
//
//#include "stdafx.h"
#include <iostream>
#include <windows.h>

#include <fstream>
#include "sclog.h"
#include "include/spdlog/spdlog.h"
//#define SPDLOG_FMT_PRINTF
std::string your_log_file_name = "Example.log";





int main(int argc, int* argv[])
{
//	namespace spd = spdlog;
	/*
	try
	{
		hik::FaultLog  SMlog;
		SMlog.seq = 1;
		SMlog.type = 2;
		SMlog.value = 3;
		int seq = 1;
		int type = 2;
		int value = 3;
		std::string filename = "spdlog_log1";
		auto console = spd::stdout_logger_mt("console"); 

		console->info("Welcome to spdlog!");
		console->info( "Creating file " + filename + ".." );

		auto file_logger = spd::rotating_logger_mt("file_logger", filename, 1024 * 1024 * 5, 3);
		file_logger->info("Log file message number", 1);

		for (int i = 0; i < 100; ++i)
		{
			auto square = i*i;
			file_logger->info("this is %d",square);
		}
	

		std::string filename2 = "Small_log2";                                                           
		auto file_loggerSM = spd::rotating_logger_mt("file_loggerSM", filename2, 1024 * 1024 * 5, 3);
		for (int u = 0; u < 100; u++)
		{
			auto square = u*u; 
			file_loggerSM->info("Welcome to spdlog2!%d",seq);
			file_loggerSM->info(u + '*' + u + '=' + square);
			
		}

		// Change log level to all loggers to warning and above
		spd::set_level(spd::level::warn);
		console->info("This should not be displayed");
		console->warn("This should!");
		spd::set_level(spd::level::info);

		// Change format pattern to all loggers
		spd::set_pattern(" **** %Y-%m-%d %H:%M:%S.%e %l **** %v");
		console->info("This should not be displayed");
		spd::get("console")->info("This is another message with different format");


		int u = 2;
		typedef hik::CLog<your_log_file_name> tlog;
		tlog::init_log();
		tlog::log("wahahaha%d\n",u);

		for (int i = 0; i < 100; ++i)
		{
			auto square = i*i;
			tlog::log("%d\n",square);
		}

	
	}
	catch (const spdlog::spdlog_ex& ex)
	{
		std::cout << "Log failed: " << ex.what() << std::endl;
	}
	getchar();
//	return 0;
}
*/
try {
	/*
	// console logger (multithreaded and with color)
	auto console = spd::stdout_logger_mt("console");
	console->info("Welcome to spdlog!");
//	console->info() << "Streams are supported too  " << 1;
	//Formatting examples
		console->info("Easy padding in numbers like {:08d}", 12);
	console->info("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
	console->info("Support for floats {:03.2f}", 1.23456);
	console->info("Positional args are {1} {0}..", "too", "supported");
	console->info("{:<30}", "left aligned");
	console->info("{:>30}", "right aligned");
	console->info("{:^30}", "centered");
	//
	// Runtime log levels
	//
	spd::set_level(spd::level::info); //Set global log level to info
	console->debug("This message shold not be displayed!");
	console->set_level(spd::level::debug); // Set specific logger's log level
	console->debug("Now it should..");

	*/
	//
	// Create a file rotating logger with 5mb size max and 3 rotated files
	//
//	hik::errLog::init_errLog();
//	hik::errLog::write(1,3);
	std::shared_ptr<spdlog::logger> _errLogger2 = spdlog::rotating_logger_mt("file_logger", "errLog", 1048576 * 5, 3);
	_errLogger2->info("hello,this is testspd");
//	errLog::init_errLog();
//	errLog::write(1, 3);

	auto file_logger = spdlog::rotating_logger_mt("file_logger", "small_log", 1048576 * 5, 3);
	
	FaultLogInfo testErrLog;
	for (int i = 0; i < 30;i++)
	{
		i++;
		testErrLog.seq = i;
		testErrLog.type = i + 1;
		testErrLog.value = 6;
		file_logger->info("{},{},{}",testErrLog.seq, testErrLog.type, testErrLog.value);
		Sleep(100);

		
	}
	
	for (int i = 0; i < 10; ++i)
 		file_logger->info("{} * {} equals {:>10}", i, i, i * i);
	//
	// Create a daily logger - a new file is created every day on 2:30am
	//
	auto daily_logger = spdlog::daily_logger_mt("daily_logger", "daily", 2, 30);

	//for (int i = 0; i < 10; ++i)
	//	daily_logger->info("{} * {} equals {:>10}", i, i, i * i);
	//
	// Customize msg format for all messages
	//
	spdlog::set_pattern("*** [%H:%M:%S %z] [thread %t] %v ***");
	file_logger->info("This is another message with custom format");
	spdlog::get("console")->info("loggers can be retrieved from a global registry using the spdlog::get(logger_name) function");
	daily_logger->info("hhahahahaha");
	// Compile time debug or trace macros.
	// Enabled #ifdef SPDLOG_DEBUG_ON or #ifdef SPDLOG_TRACE_ON
	//
	SPDLOG_TRACE(console, "Enabled only #ifdef SPDLOG_TRACE_ON..{} ,{}", 1, 3.23);
	SPDLOG_DEBUG(console, "Enabled only #ifdef SPDLOG_DEBUG_ON.. {} ,{}", 1, 3.23);

	// Asynchronous logging is very fast..
	// Just call spdlog::set_async_mode(q_size) and all created loggers from now on will be asynchronous..
	//
	size_t q_size = 1048576; //queue size must be power of 2
	spdlog::set_async_mode(q_size);
	auto async_file = spdlog::daily_logger_st("async_file_logger", "async_log.txt");
	async_file->info("This is async log..Should be very fast!");// << "This is async log.." << "Should be very fast!";
	//
	// syslog example. linux only..
	//
	getchar();

	std::string ident = "spdlog-example";
	auto syslog_logger = spdlog::syslog_logger("syslog", ident, LOG_PID);
	syslog_logger->warn("This is warning that will end up in syslog. This is Linux only!");


}
catch (const spdlog::spdlog_ex& ex) {
	std::cout << "Log failed: " << ex.what() << std::endl;
}
}

/*// Example of user defined class with operator<<
class some_class {};
std::ostream& operator<<(std::ostream& os, const some_class& c)
{
	return os << "some_class";
}

void custom_class_example()
{
	some_class c;
	spdlog::get("console")->info("custom class with operator<<: {}..", c);
	spdlog::get("console")->info("custom class with operator<<: "); //<< "custom class with operator<<: " << c << "..";
}
*/