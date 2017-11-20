#include <iostream>
#include "include/spdlog/spdlog.h"

int main()
{
	namespace spd = spdlog;

	try
	{
		std::string filename = "spdlog_example";
		auto console = spd::stdout_logger_mt("console");
		console->info("Welcome to spdlog!");
		console->info( "Creating file " + filename + "..");

		auto file_logger = spd::rotating_logger_mt("file_logger", filename, 1024 * 1024 * 5, 3);
		file_logger->info("Log file message number", 1);

		for (int i = 0; i < 100; ++i)
		{
			auto square = i*i;
			file_logger->info(  i + '*' + i + '=' + square);
		}

		// Change log level to all loggers to warning and above
		spd::set_level(spd::level::warn);
		console->info("This should not be displayed");
		console->warn("This should!");
		spd::set_level(spd::level::info);

		// Change format pattern to all loggers
		spd::set_pattern(" **** %Y-%m-%d %H:%M:%S.%e %l **** %v");
		spd::get("console")->info("This is another message with different format");
	}
	catch (const spd::spdlog_ex& ex)
	{
		std::cout << "Log failed: " << ex.what() << std::endl;
	}
	getchar();
//	return 0;
}
